#pragma once

#include<iostream>
#include<unordered_map>

#include "loader.hpp"
#include "memory.hpp"
#include "var_t.hpp"
#include "function_t.hpp"

csvm::var_t print(const std::vector<csvm::var_t> &argv)
{
    for (auto x : argv) {
        if (x.type_tag.extend_type == 0){
            if(x.type_tag.building_type == 1)
                std::cout << int(x.data) << std::endl;
            else
                std::cout<< reinterpret_cast<float&>(x.data) << std::endl;
        }
    }
    return csvm::var_t(0x00000001, 0x00008001);
}

csvm::var_t input(const std::vector<csvm::var_t> &argv)
{
    std::uint32_t res = 0xffffffff;
    std::string str;
    if(argv.empty())
        std::cin>>str;
    else
        throw std::invalid_argument("arguments of input() must be 0.");
    if(str.find('.') != std::string::npos) {
        res = (std::uint32_t)(std::stof(str));
        return csvm::var_t(0x00000002, res);
    }
    else {
        res = std::stoi(str);
        return csvm::var_t(0x00000001, res);
    }
}

csvm::extend_function_t b_print = &print, b_input = &input;

namespace csvm {
	class vm_t {
	private:

		std::unordered_map<std::uint16_t, void *> function_table = {{0x8001, reinterpret_cast<void *>(b_print)},{0x8000,reinterpret_cast<void *>(b_input)}};
		csvm::stack<csvm::building_function_t::frame_t> building_function_frame_stack;
		csvm::stack<var_t> var_stack;

		struct {
			bool load_functions_and_function_table = false;
		} step;

		inline int addr(const std::uint16_t &ui16){
		    return int(ui16 == 0xffff ? var_stack.top().data : ui16);
		}
	public:
		vm_t() = default;

		~vm_t() {}

		void load_functions(const std::string &path)
		{
			std::vector<std::uint32_t> ins_stream; // prepare ins stream
			csvm::loader::load_ins_stream_from_file(path, ins_stream); // load ins stream from file
			std::uint8_t ui8_opcode;
			std::uint16_t ui16_operand;
			void *cur_fun = nullptr;
			if (csvm::ui8_to_opcode((ins_stream[0] & 0xff000000) >> 24) != csvm::opcode::SUBP)
				throw std::runtime_error("content bytecode file must started as SUBP.");
			for (int i = 0; i < ins_stream.size(); ++i) {
				ui8_opcode = (ins_stream[i] & 0xff000000) >> 24;
				ui16_operand = ins_stream[i] & 0x00ffffff;
				switch (ui8_to_opcode(ui8_opcode)) {
                    case csvm::opcode::SUBP:
                        cur_fun = new csvm::building_function_t;
                        function_table[ui16_operand] = cur_fun;
                        continue;
                    case csvm::opcode::DATA:
//    					reinterpret_cast<csvm::building_function_t *>(cur_fun)->data_seg.emplace_back(
//    					    csvm::data_t::frame_t{(ins_stream[i] & 0x00ff0000) >> 16,
//    					                          std::vector<std::uint32_t>()});
//    					reinterpret_cast<csvm::building_function_t *>(cur_fun)->data_seg.back().vec_ui32.reserve(
//    					    ui16_operand);
                        for (int j = 1; j <= ui16_operand; ++j)
//    						reinterpret_cast<csvm::building_function_t *>(cur_fun)->data_seg.back().vec_ui32.emplace_back(
//    						    ins_stream[i + j]);
                                reinterpret_cast<csvm::building_function_t *>(cur_fun)->data_seg.emplace_back(csvm::var_t((ins_stream[i]>>16)&0x00ff,ins_stream[i+j]));
                        i += ui16_operand;
                        continue;
                    default:
                        reinterpret_cast<csvm::building_function_t *>(cur_fun)->ins_stack.push(ins_stream[i]);
                    break;
				}
			}
			if (csvm::ui8_to_opcode((reinterpret_cast<csvm::building_function_t *>(cur_fun)->ins_stack.top()) >> 24) !=
			        csvm::opcode::FEOF)
				throw std::runtime_error(
				    "\"FEOF\" was not found while loading bytecode file. This will probably be not safe.");
			else
				reinterpret_cast<csvm::building_function_t *>(cur_fun)->ins_stack.pop();
			step.load_functions_and_function_table = true;


			for (auto p : function_table) {
				if ((p.first & 0x8000) == 0x8000)
					continue;
				int i = 0, j = 0;
				std::cerr << "\n\n========================" << std::endl;
				std::cerr << "in function " << p.first << std::endl;
				std::cerr << "========================" << std::endl;
				std::cerr << "||data-seg||" << std::endl;
				std::cerr << "||        ||" << std::endl;
				for (auto da : reinterpret_cast<building_function_t *>(p.second)->data_seg) {
					std::cerr << std::dec << i++ << ":\tvar_type: ";
					std::cerr << std::hex << std::setfill('0') << std::setw(2)
					          << (reinterpret_cast<std::uint16_t &>(da.type_tag.building_type) & 0xff) << " value: ";
						std::cerr << std::hex << std::setfill('0') << std::setw(8) << da.data ;
						if((reinterpret_cast<std::uint16_t &>(da.type_tag.building_type) & 0xff) == 2)
						    std::cerr << "(float:" << std::fixed << reinterpret_cast<float &>(da.data) <<")";
                        std::cerr << std::endl;
				}
				std::cerr << "||ins-seg||" << std::endl;
				std::cerr << "||       ||" << std::endl;
				for (auto in : reinterpret_cast<building_function_t *>(p.second)->ins_stack.elm) {
					std::cerr << std::dec << j++ << ":\t||\t";
					std::cerr << std::hex << std::setfill('0') << std::setw(8) << in << std::endl;
				}
			}

		}

		/*
		 * true: continue to run current frame
		 * false: need to run other frame
		 */
		inline bool exec_one_ins(csvm::building_function_t::frame_t &frame)
		{
			const std::uint32_t ui32_ins = frame.function->ins_stack.elm[frame.pc];
			const std::uint16_t ui16_operand = ui32_ins & (0x0000ffff);
			const std::uint8_t  ui8_method = (ui32_ins & (0x00ff0000)) >> 16;
			csvm::opcode enum_opcode = csvm::ui8_to_opcode((ui32_ins & (0xff000000)) >> 24);
			int &pc = frame.pc, ss = frame.ss;

			switch (enum_opcode) { // faster (handling operand in each case)

			case csvm::opcode::SUBP:
				throw std::runtime_error("There has not filtered SUBP instruction.");
				break;

			case csvm::opcode::DATA:
				throw std::runtime_error("There has not filtered DATA instruction.");
				break;

			// do nothing
			case csvm::opcode::NONE:
				break;

			// push int32(low16) into var_stack
			case csvm::opcode::PLBI:
				var_stack.push(csvm::var_t(0x00000001, ui16_operand));
				std::cerr << "PLBI: " << std::hex << var_stack.top().data << "(hex) " << std::dec
				          << var_stack.top().data << "(dec)" << std::endl;
				break;

			// push int32(high16) into var_stack
			case csvm::opcode::PHBI:
				var_stack.top().data |= (ui16_operand << 16);
				std::cerr << "PHBI: " << std::hex << var_stack.top().data << "(hex) " << std::dec
				          << var_stack.top().data << "(dec)" << std::endl;
				break;

			// push float32(low16) into var_stack
			case csvm::opcode::PLBF:
				var_stack.push(csvm::var_t(0x00000002, ui16_operand));
				std::cerr << "PLBF: " << std::fixed << var_stack.top().data << "(float) " << std::endl;
				break;

			// push float32(high16) into var_stack
			case csvm::opcode::PHBF:
				var_stack.top().data |= (ui16_operand << 16);
				std::cerr << "PHBF: " << std::fixed << reinterpret_cast<float &>(var_stack.top().data) << "(float) " << std::endl;
				break;

			case opcode::PDAT: {
//				auto data_frame = frame.function->data_seg[ui16_operand];
//				if ((data_frame.type_tag.building_type != 0))
//					var_stack.push(csvm::var_t(data_frame.type_tag, data_frame.vec_ui32.operator[](0)));
//				else
//					var_stack.push(csvm::var_t(data_frame.type_tag, new std::vector<std::uint32_t>(
//					                               data_frame.vec_ui32)));

                var_stack.push(frame.function->data_seg[addr(ui16_operand)]);
                std::cerr << "PDAT: " << int(var_stack.top().type_tag.building_type) << " ";
                if(var_stack.top().type_tag.building_type == 1)
                    std::cerr << var_stack.top().data;
                else
                    std::cerr << reinterpret_cast<float &>(var_stack.top().data);
                std::cerr << std::endl;
			}
			break;

			case opcode::PUSH: {
				bool re_direct = (ui8_method) == 0xff;
                std::cerr << "PUSH: push ";
                if (re_direct) {
					if(var_stack.top(addr(ui16_operand)).type_tag.building_type==1)
					    std::cerr << reinterpret_cast<int &>(var_stack.top(addr(ui16_operand)).data);
					else
                        std::cerr << reinterpret_cast<float &>(var_stack.top(addr(ui16_operand)).data);
                    var_stack.push(var_stack.top(addr(ui16_operand)));
				}
				else {
                    if(var_stack.elm[frame.ss + addr(ui16_operand)].type_tag.building_type==1)
                        std::cerr << reinterpret_cast<int &>(var_stack.elm[frame.ss + addr(ui16_operand)].data);
                    else
                        std::cerr << reinterpret_cast<float &>(var_stack.elm[frame.ss + addr(ui16_operand)].data);
                    var_stack.push(var_stack.elm[frame.ss + addr(ui16_operand)]);
				}
				std::cerr << " into var_stack top;" << std::endl;
			}
			break;

			case opcode::COPY: {
				bool re_direct = ((ui8_method & 0x0f) != 0x00);
				std::cerr<<"COPY: var_stack";
				if(re_direct)
                    std::cerr << ".top(" << addr(ui16_operand) << ") = ";
				else
                    std::cerr << "[" << addr(ui16_operand) << "] = ";
				if(var_stack.top().type_tag.building_type == 1)
				    std::cerr << reinterpret_cast<int &>(var_stack.top().data);
				else
                    std::cerr << reinterpret_cast<float &>(var_stack.top().data);
				if((ui8_method & 0xf0) == 0x00)
				    std::cerr << " and pop";
				std::cerr << "." << std::endl;

				switch (ui8_method & 0xf0) {
				case 0x00:
					if (re_direct)
                        var_stack.top(addr(ui16_operand)) = var_stack.top();
					else
						var_stack.elm[frame.ss + addr(ui16_operand)] = var_stack.top();
					var_stack.pop();
					break;
				case 0xf0:
					if (re_direct)
						var_stack.top(addr(ui16_operand)) = var_stack.top();
					else
					    var_stack.elm[frame.ss + addr(ui16_operand)] = var_stack.top();
					break;
				}
			}
			break;

            case csvm::opcode::SPOP:
                var_stack.pop(ui16_operand);
                std::cerr << "SPOP: var_stack has poped " << ui16_operand << " times." << std::endl;
            break;

			// add from stack * stack
			case csvm::opcode::SADD:
				var_stack.top(1) += var_stack.top();
				var_stack.pop();
				if(var_stack.top().type_tag.building_type==1)
				    std::cerr << "SADD: " << std::hex << var_stack.top().data << "(hex) " << std::dec
				          << var_stack.top().data << "(dec)" << std::endl;
				else
                    std::cerr << "SADD: " << std::fixed << reinterpret_cast<float &>(var_stack.top().data) << std::endl;
            break;
			case csvm::opcode::SSUB:
				var_stack.top(1) -= var_stack.top();
				var_stack.pop();
                if(var_stack.top().type_tag.building_type==1)
				    std::cerr << "SSUB: " << std::hex << var_stack.top().data << "(hex) " << std::dec
				          << var_stack.top().data << "(dec)" << std::endl;
                else
                    std::cerr << "SSUB: " << std::fixed << reinterpret_cast<float &>(var_stack.top().data) << std::endl;
            break;

			case csvm::opcode::SMUL:
				var_stack.top(1) *= var_stack.top();
				var_stack.pop();
                if(var_stack.top().type_tag.building_type==1)
				    std::cerr << "SMUL: " << std::hex << var_stack.top().data << "(hex) " << std::dec
				          << var_stack.top().data << "(dec)" << std::endl;
                else
                    std::cerr << "SMUL: " << std::fixed << reinterpret_cast<float &>(var_stack.top().data) << std::endl;
            break;

			case csvm::opcode::SDIV:
				var_stack.top(1) /= var_stack.top();
				var_stack.pop();
                if(var_stack.top().type_tag.building_type==1)
				    std::cerr << "SDIV: " << std::hex << var_stack.top().data << "(hex) " << std::dec
				          << var_stack.top().data << "(dec)" << std::endl;
                else
                    std::cerr << "SDIV: " << std::fixed << reinterpret_cast<float &>(var_stack.top().data) << std::endl;
            break;

				// immediately add, operating top of var_stack, size of stack will not change.
			case csvm::opcode::IADD:
                var_stack.top() += var_t(0x00000001,ui16_operand);
                std::cerr << "IADD: " << std::hex << var_stack.top().data << "(hex) " << std::dec
                          << var_stack.top().data << "(dec)" << std::endl;
            break;
			case csvm::opcode::ISUB:
                var_stack.top() -= var_t(0x00000001,ui16_operand);
                std::cerr << "ISUB: " << std::hex << var_stack.top().data << "(hex) " << std::dec
                          << var_stack.top().data << "(dec)" << std::endl;
            break;
			case csvm::opcode::IMUL:
                var_stack.top() *= var_t(0x00000001,ui16_operand);
                std::cerr << "IMUL: " << std::hex << var_stack.top().data << "(hex) " << std::dec
                          << var_stack.top().data << "(dec)" << std::endl;
            break;
			case csvm::opcode::IDIV:
                var_stack.top() /= var_t(0x00000001,ui16_operand);
                std::cerr << "IDIV: " << std::hex << var_stack.top().data << "(hex) " << std::dec
                          << var_stack.top().data << "(dec)" << std::endl;
            break;

			case opcode::DADD:
				break;
			case opcode::DSUB:
				break;
			case opcode::DMUL:
				break;
			case opcode::DDIV:
				break;

			// jump to
			case csvm::opcode::NJMP:
				pc = ui16_operand;
				std::cerr << "NJMP: jump to " << ui16_operand << " " << csvm::ui8_to_string((frame.function->ins_stack.elm[ui16_operand])>>24) << std::endl;
            return true;
				break;

			// jump while stack.top()>0
			case csvm::opcode::CJMP:{ // just int
                if (((var_stack.top() > 0) && (ui8_method == 0x00)) || ((var_stack.top() == 0) && (ui8_method == 0xff))) {
                    pc = ui16_operand;
                    std::cerr << "CJMP: jump to " << ui16_operand << " "
                              << csvm::ui8_to_string((frame.function->ins_stack.elm[ui16_operand]) >> 24)
                              << std::endl;
                    var_stack.pop();
                    return true;
                } else {
                    var_stack.pop();
                    std::cerr << "CJMP: jump failed" << std::endl;
                }
            }
            break;

			// call a function (sp has updating)
			case csvm::opcode::CALL: {
				++pc;
				int argc = ((ui32_ins & 0xff0000) >> 16);
				if (ui16_operand & 0x8000) {
					try {
						var_stack.push(reinterpret_cast<csvm::extend_function_t>(function_table[ui16_operand])(std::vector<var_t>(var_stack.elm.end() - argc, var_stack.elm.end())));
					}
					catch (...) {
						std::cerr << "ldc is fucking himself." << std::endl;
					}
					std::cerr<< "CALL exfun[" << ui16_operand << "], return value = " << var_stack.top().data << std::endl;
					return true;
				}
				else {
                    building_function_frame_stack.push(csvm::building_function_t::frame_t(
                            reinterpret_cast<csvm::building_function_t *>(function_table[ui16_operand]),
                            var_stack.size() - argc));
                    std::cerr << "CALL: call [" << ui16_operand << "], pc of current frame = "
                              << building_function_frame_stack.elm[building_function_frame_stack.size() - 2].pc
                              << std::endl;
                    return false;
                }
			}
			break;

			case csvm::opcode::RETP:
                var_stack.elm[ss] = var_stack.top();
                var_stack.pop_to(ss + 1);
				std::cerr << "RETP: return value = " << var_stack.top().data << std::endl;
				building_function_frame_stack.pop();
            return false;

			// end of file
			case csvm::opcode::FEOF:
                std::cerr << "FEOF: end of file" << std::endl;
            return false;

			case csvm::opcode::ERROR:
				throw std::runtime_error("running bytecode: instruction " + std::to_string(frame.function->ins_stack.elm[pc]) + "(pc = "+std::to_string(pc)+" ) error.");
			}
			++pc;
			return true;
		}

		int start()
		{
			if (step.load_functions_and_function_table) {
			    std::cerr<<"********************";
			    std::cerr<<"mian ins_seg size:"<<reinterpret_cast<csvm::building_function_t *>(function_table[0])->ins_stack.size()<<std::endl;
				building_function_frame_stack.push(csvm::building_function_t::frame_t(
				                                       reinterpret_cast<csvm::building_function_t *>(function_table[0]), 0));
				while (!building_function_frame_stack.empty()) {
					while (exec_one_ins(building_function_frame_stack.top())) {
						//each execution of ins in a frame
					}
					// enter a frame or exit a frame (top of frames_stack has changed)
				}
			}
			else {
				throw std::runtime_error("The csvm has not initialed thread frames yet, so can not start.");
			}
			std::cerr << "var_stack remain: " << var_stack.size() <<" elements." << std::endl;
			std::cerr << "c++ main received: "
			          << (var_stack.empty() ? 0 : reinterpret_cast<std::int32_t &>(var_stack.top().data))
			          << std::endl;
			return var_stack.empty() ? 0 : reinterpret_cast<std::int32_t &>(var_stack.top().data);
		}
	};
}