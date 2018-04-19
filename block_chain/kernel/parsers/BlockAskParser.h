//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKASKPARSER_H
#define BLOCK_CHAIN_BLOCKASKPARSER_H


#include "MessageParser.h"

class BlockAskParser: public MessageParser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};

#endif //BLOCK_CHAIN_BLOCKASKPARSER_H