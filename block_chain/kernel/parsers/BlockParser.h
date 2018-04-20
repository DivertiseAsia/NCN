//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKPARSER_H
#define BLOCK_CHAIN_BLOCKPARSER_H


#include "MessageParser.h"

/**
 *  A message parser linked to a BlockMessage.
 *  @see Message
 *  @see BlockMessage
 *  @see MessageParser
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class BlockParser: public MessageParser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};


#endif //BLOCK_CHAIN_BLOCKPARSER_H
