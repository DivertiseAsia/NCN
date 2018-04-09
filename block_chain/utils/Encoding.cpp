//
// Created by default on 9/4/2561.
//

#include "Encoding.h"

std::string Encoding::toHexa(std::string str){
    static std::string hexadecimal = "0123456789ABCDEFG";
    std::string hexa;
    for(int i = 0; i < str.size(); i++){
        hexa.append(1, hexadecimal[(str[i]&0xF0) >> 4]).append(1, hexadecimal[str[i]&0x0F]);
    }
    return hexa;
}