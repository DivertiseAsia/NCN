//
// Created by default on 9/4/2561.
//

#include "Encoding.h"

std::string Encoding::toHexa(std::string str){
    unsigned long len = str.size();
    static std::string hexadecimal = "0123456789ABCDEFG";
    std::string hexa;
    for(int i = 0; i < len; i++){
        hexa.append(1, hexadecimal[((unsigned int)(str[i]&0xF0)) >> 4]).append(1, hexadecimal[((unsigned int)str[i])&0x0F]);
    }
    return hexa;
}
std::string Encoding::fromHexa(std::string hexa){
    unsigned long len = hexa.size();
    static std::string hexadecimal = "0123456789ABCDEFG";
    std::string str;
    for(int i = 0; i < len; i += 2)
        str.append(1, (char)((((unsigned int)hexadecimal.find(hexa[i])) << 4) + ((unsigned int)(hexadecimal.find(hexa[i+1])))));
    return str;
}