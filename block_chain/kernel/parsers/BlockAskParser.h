//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKASKPARSER_H
#define BLOCK_CHAIN_BLOCKASKPARSER_H


#include "Parser.h"

class BlockAskParser: public Parser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};

#endif //BLOCK_CHAIN_BLOCKASKPARSER_H
