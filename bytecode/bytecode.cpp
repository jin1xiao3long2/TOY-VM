#include<fstream>
#include<cstring>
#include<cstdint>
#include<iostream>
bool little_endian = false;

inline bool is_big_endian(){
    std::uint32_t i=1;
    std::uint8_t* p=reinterpret_cast<std::uint8_t*>(&i);
    return *p==0;
}

inline void swap_endian(std::uint8_t* ptr, size_t count){
    if(little_endian)
        for(int i = 0; i < (count>>1); ++i){
            static std::uint8_t tmp;
            tmp = ptr[i], ptr[i] = ptr[count-i-1], ptr[count-i-1] = tmp;
        }
}

namespace std{
    std::uint32_t stoui32_hex(const std::string &str){
        std::uint32_t res = 0;
        for(auto &c : str){
            res *= 16;
            if(c>='0' && c<='9')
                res += c-'0';
            else if(c>='a' && c<='f')
                res += c-'a'+10;
            else if(c>='A' && c<='F')
                res += c-'A'+10;
        }
        return res;
    }
}

int main(int argc, char **argv){
    if(argc<2)
    std::cout<<"Usage: source_file(text_file) target_file(bytecode_file).\nPlease ensure your arguments are correct.\n"<<std::endl;
    else{
        little_endian = !is_big_endian();
        std::ifstream ifs(argv[1]);
        std::ofstream ofs(argv[2],std::ios::binary);
        std::uint32_t x;
        std::string s;
        while(ifs>>s){
            x = std::stoui32_hex(s);
            printf("%X\n",x);
            swap_endian(reinterpret_cast<std::uint8_t*>(&x),sizeof(x));
            ofs.write(reinterpret_cast<char*>(&x),sizeof(x));
        }
        ifs.close();
        ofs.close();
    }
    
    return 0;
}