//
// Created by default on 9/4/2561.
//

#ifndef BLOCK_CHAIN_ENCODING_H
#define BLOCK_CHAIN_ENCODING_H

#include "string"
#include <cstring>

class Encoding {
public:
    static std::string toHexa(std::string str);
    static std::string fromHexa(std::string str);
};


#endif //BLOCK_CHAIN_ENCODING_H
