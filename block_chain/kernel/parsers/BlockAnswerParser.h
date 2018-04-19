//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKANSWERPARSER_H
#define BLOCK_CHAIN_BLOCKANSWERPARSER_H


#include "Parser.h"

class BlockAnswerParser: public Parser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};


#endif //BLOCK_CHAIN_BLOCKANSWERPARSER_H
