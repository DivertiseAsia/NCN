//
// Created by default on 9/4/2561.
//

#ifndef BLOCK_CHAIN_ENCODING_H
#define BLOCK_CHAIN_ENCODING_H

#include "string"
#include <cstring>

/**
 *  @class Encoding "block_chain/utils/Encoding.h"
 *  An encoding util.
 *  The static class encoding allows to encode any string in
 *  hexadecimal and get any text from its hexadecimal form.
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class Encoding {
public:

    /**
     *  Encode a given text in hexadecimal
     *
     *  @param str string to be converted
     *  @return the encoded string
     */
    static std::string toHexa(std::string str);

    /**
     *  Decode a given text from hexadecimal
     *
     *  @param str string to be converted
     *  @return the decoded string
     */
    static std::string fromHexa(std::string str);
};


#endif //BLOCK_CHAIN_ENCODING_H
