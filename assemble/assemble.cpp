#include<fstream>
#include<string>
#include<cstdint>
#include<iostream>
#include<vector>
#include<unordered_map>
std::unordered_map<std::string,std::uint8_t> str_to_ui8 = {
    {"SUBP",0xF0},
    {"DATA",0xF1},
    {"PLBI",0x01}, //
    {"PHBI",0x02}, //
    {"PLBF",0x03}, //
    {"PHBF",0x04}, //
    {"PDAT",0x05},
    {"PUSH",0x06},
    {"COPY",0x07}, 
    {"SPOP",0x08},
    {"SADD",0x10},
    {"IADD",0x11},
    {"DADD",0x12},
    {"SSUB",0x13},
    {"ISUB",0x14},
    {"DSUB",0x15},
    {"SMUL",0x16},
    {"IMUL",0x17},
    {"DMUL",0x18},
    {"SDIV",0x19},
    {"IDIV",0x1A},
    {"DDIV",0x1B},
    {"NJMP",0x20},
    {"CJMP",0x21},
    {"CALL",0x22},
    {"RETP",0x23},
};
std::vector<std::string> split(std::string s){
    std::vector<std::string> res;
    std::string buf;
    for(auto c : s){
        if(c==' ')
            res.emplace_back(buf),
            buf.clear();
        else
            buf.push_back(c);
    }
    if(!buf.empty())
        res.emplace_back(buf);
    return res;
}

std::unordered_map<std::string,std::uint32_t> fun_to_id = {{"main",0},{"print",0x00008001},{"input",0x00008000}};
int building_fun = 0;
std::unordered_map<std::string,std::uint32_t> flag_to_text_line;
std::unordered_map<std::uint32_t,std::uint32_t> text_line_to_pc;
std::uint32_t addr(std::string str){
    return str == "ffff" ? 0x0000ffff : (0xffff & (std::stoi(str)));
}

void load_text_stream(std::string path, std::vector<std::vector<std::string>> &text_stream){
    std::ifstream ifs(path);
    if(!ifs.is_open())
        throw std::invalid_argument("path wrong.");
    std::string s;
    while(getline(ifs,s))text_stream.emplace_back(split(s));
    ifs.close();
}


void filter_flag(std::vector<std::vector<std::string>>&text_stream){
    std::vector<std::vector<std::string>> res;
    for(int i = 0; i < text_stream.size(); ++i){
        auto args = text_stream[i];
        if(args[0] == "FLAG"){
            flag_to_text_line[args[1]] = res.size();
            for(;i<text_stream.size() && (text_stream[i][0]=="FLAG" || text_stream[i][0] == "DATA" || text_stream[i][0] == "SUBP"); ++i);
        }
        res.emplace_back(text_stream[i]);
    }
    text_stream.clear();
    text_stream = res;
}
void fill_flag(std::vector<std::uint32_t> &ins_stream){
    std::uint32_t pc;
    for(auto &x : ins_stream)
        switch((x&0xff000000)>>24){
        case 0x20:
            pc = (text_line_to_pc[(x&0x0000ffff)] & 0x0000ffff);
            x &= 0xffff0000;
            x |= pc;
        break;
        case 0x21:
            if(text_line_to_pc.find(x&0x0000ffff)==text_line_to_pc.end())
                continue;
            pc = text_line_to_pc[(x&0x0000ffff)];
            x &= 0xffff0000;
            x |= pc;
        break;
        default:
        continue;
    }
}
void text_to_ui32(std::vector<std::vector<std::string>> text_stream, std::vector<std::uint32_t> &ins_stream){
    ins_stream.clear();
    int pc = -1;
    for(int i = 0; i < text_stream.size(); ++i){

        const auto args = text_stream[i];
        std::uint32_t ui32_ins = 0;
        ui32_ins = (str_to_ui8[args[0]] << 24);

        switch(str_to_ui8[args[0]]){
            case 0xF0:
                pc = -1;
                if(args[1] != "main")
                    fun_to_id[args[1]] = ++building_fun;
                ui32_ins |= (0x0000ffff & fun_to_id[args[1]]);
            break;
            case 0xF1:
                if(args[1]=="int")
                    ui32_ins |= (0x00010000);
                else if(args[1]=="float")
                    ui32_ins |= (0x00020000);
                else 
                    throw std::runtime_error("error type of data.");
                ui32_ins |= (0x0000ffff & std::stoi(args[2]));
                ins_stream.emplace_back(ui32_ins);


                for(int j = 1 ; j <= std::stoi(args[2]); ++j){

                    if(args[1]=="int") {
                        int tmp;
                        tmp = std::stoi(args[2 + j]);
                        ins_stream.emplace_back(reinterpret_cast<std::uint32_t &>(tmp));
                    }
                    else {
                        float tmp;
                        tmp = std::stof(args[2 + j]);
                        ins_stream.emplace_back(reinterpret_cast<std::uint32_t &>(tmp));
                    }
                }

            continue;
            case 0x05:
                ++pc;
                ui32_ins |= addr(args[1]);
            break;
            case 0x06:
                switch(args.size()){
                    
                    case 2: {
                        ++pc;
                        std::uint32_t res;
                        if (args[1].find('.') == std::string::npos) {
                            res = std::stoi(args[1]);
                            ins_stream.emplace_back(0x01000000 | (0x0000ffff & res));
                            if((0xffff0000 & res)!=0)
                                ins_stream.emplace_back(0x02000000 | ((0xffff0000 & res) >> 16) ),
                                ++pc;
                        } else {
                            float tmp = std::stof(args[1]);
                            res = reinterpret_cast<std::uint32_t &>(tmp);
                            ins_stream.emplace_back(0x03000000 | (0x0000ffff & res));
                            if((0xffff0000 & res)!=0)
                                ins_stream.emplace_back(0x04000000 |((0xffff0000 & res) >> 16)),
                                ++pc;
                        }
                    }
                    break;

                    case 3:
                        ++pc;
                        if(args[1] == "00" || args[1] == "ff"){
                            std::uint32_t method;
                            if(args[1]=="ff")
                                method = 0x00ff0000;
                            else
                                method = 0x00000000;
                            ins_stream.emplace_back(0x06000000 | method | std::stoi(args[2]));
                        }
                        else
                            throw std::runtime_error("wrong method of PUSH.");
                    break;

                    default:
                        throw std::runtime_error("wrong arguments of PUSH.");
                }
            text_line_to_pc[i] = pc;
            continue;
            case 0x07:
                ++pc;
                if(args.size() == 3){
                    if(args[1] == "00" || args[1] == "ff" || args[1] == "0f" || args[1] == "f0"){
                            std::uint32_t method;
                            if(args[1]=="00")
                                method = 0x00000000;
                            else if(args[1]=="ff")
                                method = 0x00ff0000;
                            else if(args[1]=="0f")
                                method = 0x000f0000;
                            else
                                method = 0x00f00000;
                            ui32_ins |= (method | addr(args[2]));
                        }
                        else
                            throw std::runtime_error("wrong method of COPY.");
                }
                else {
                    throw std::runtime_error("wrong arguments of COPY.");
                }
            break;
            case 0x08:
                ++pc;

                switch(args.size()){
                    case 2:
                        ui32_ins |= (std::stoi(args[1]));
                    break;
                    case 3:
                        if(args[1] == "00" || args[1] == "ff" || args[1] == "0f" || args[1] == "f0"){
                                std::uint32_t method;
                                if(args[1]=="00")
                                    method = 0x00000000;
                                else if(args[1]=="ff")
                                    method = 0x00ff0000;
                                else if(args[1]=="0f")
                                    method = 0x000f0000;
                                else
                                    method = 0x00f00000;
                                ui32_ins |= (method | std::stoi(args[2]));
                        }
                        else
                            throw std::runtime_error("wrong method of SPOP.");
                    break;
                    default:
                        throw std::runtime_error("wrong arguments of SPOP." + std::to_string(args.size()));
                }

            break;
            case 0x10:
                ++pc;
            break;
            case 0x11:
                ++pc;
                ui32_ins |= (0x0000ffff & std::stoi(args[1]));
            break;
            case 0x12:
                ++pc;
                ui32_ins |= (0x0000ffff & addr(args[1]));
            break;
            case 0x13:
                ++pc;
            break;
            case 0x14:
                ++pc;
                ui32_ins |= (0x0000ffff & std::stoi(args[1]));
            break;
            case 0x15:
                ++pc;
                ui32_ins |= (0x0000ffff & addr(args[1]));
            break;
            case 0x16:
                ++pc;
            break;
            case 0x17:
                ++pc;
                ui32_ins |= (0x0000ffff & std::stoi(args[1]));
            break;
            case 0x18:
                ++pc;
                ui32_ins |= (0x0000ffff & addr(args[1]));
            break;
            case 0x19:
                ++pc;
            break;
            case 0x1A:
                ++pc;
                ui32_ins |= (0x0000ffff & std::stoi(args[1]));
            break;
            case 0x1B:
                ++pc;
                ui32_ins |= (0x0000ffff & addr(args[1]));
            break;
            case 0x20:
                ++pc;
//                std::cout<<args[0]<<" "<<args[1]<<": line = "<<flag_to_text_line[args[1]] << std::endl;
                ui32_ins |= (0x0000ffff & flag_to_text_line[args[1]]);
            break;
            case 0x21:
                ++pc;
//                std::cout<<args[0]<<" "<<args[1]<<": line = "<<flag_to_text_line[args[1]] << std::endl;
                ui32_ins |= (0x0000ffff & flag_to_text_line[args[1]]);
            break;
            case 0x22:
                ++pc;
                ui32_ins |= (0x00ff0000 & (std::stoi(args[1]) << 16)) | (0x0000ffff & fun_to_id[args[2]]) ;
            break;
            case 0x23:
                ++pc;
            break;
        }
        text_line_to_pc[i] = pc;
        ins_stream.emplace_back(ui32_ins);
    }
}
void save(std::string path, std::vector<std::uint32_t> &ins_stream){
    std::ofstream ofs(path);
    if(!ofs.is_open())
        throw std::runtime_error("saving " + path + " failed.");
    ofs<<"deadface"<<std::endl;
    for(auto &x : ins_stream)
        ofs<<x<<std::endl;
    ofs<<"ff000000"<<std::endl;
    ofs.close();
}

int main(int argc, char **argv){

    try{
        std::vector<std::uint32_t> ins_stream;
        std::vector<std::vector<std::string>> text_stream;
        load_text_stream(argv[1], text_stream);
        filter_flag(text_stream);
        text_to_ui32(text_stream, ins_stream);
        fill_flag(ins_stream);
        save(argv[2],ins_stream);
//        std::cout<<"deadface"<<std::endl;
//        for (auto x : ins_stream) {
//            std::cout <<std::hex<< x << std::endl;
//        }
//        std::cout<<"ff000000"<<std::endl;
        return 0;
    }catch(std::exception &e){
        std::cout<<e.what();
    }
}

