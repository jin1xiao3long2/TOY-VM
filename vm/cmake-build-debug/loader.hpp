#pragma once

#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<iostream>
#include<iomanip>

#include"memory.hpp"
#include"framework.hpp"

namespace csvm {
	namespace loader {
		inline bool is_big_endian()
		{
			std::uint32_t i = 1;
			std::uint8_t *p = reinterpret_cast<std::uint8_t *>(&i);
			return *p == 0;
		}

		inline void swap_endian(std::uint8_t *ptr, size_t count)
		{
			if (!is_big_endian()) //faster
				for (int i = 0; i < (count >> 1); ++i) {
					static std::uint8_t tmp;
					tmp = ptr[i], ptr[i] = ptr[count - i - 1], ptr[count - i - 1] = tmp;
				}
		}

		template<typename T>
		void vm_bin_read(std::ifstream &ifs, T &var)
		{
			ifs.read(reinterpret_cast<char *>(&var), sizeof(T));
			swap_endian(reinterpret_cast<std::uint8_t *>(&var), sizeof(T));
		}

		void load_ins_stream_from_file(const std::string &path, std::vector<std::uint32_t> &ins_stream)
		{
			ins_stream.clear();
			std::ifstream ifs(path, std::ios::binary);
			if (!ifs.is_open())
				throw std::invalid_argument(path + " is not found.");

			std::uint32_t ui32_ins;
			vm_bin_read(ifs, ui32_ins);
			if (ui32_ins != file_header_magic)
				throw std::runtime_error("loading bytecode: format error.");

			std::cerr << "loading ins:" << std::endl;
			while (csvm::ui8_to_opcode(ui32_ins >> 24) != csvm::opcode::FEOF) {
				vm_bin_read(ifs, ui32_ins);
				ins_stream.emplace_back(ui32_ins);
			}
			std::cerr << "========================\n\n" << std::endl;
			ifs.close();
		}
	}
}