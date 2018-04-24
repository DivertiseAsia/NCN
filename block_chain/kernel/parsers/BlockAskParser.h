//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKASKPARSER_H
#define BLOCK_CHAIN_BLOCKASKPARSER_H


#include "MessageParser.h"

/**
 *  @class BlockAskParser "block_chain/kernel/parsers/BlockAskParser.h"
 *  A message parser linked to a BlockAskMessage.
 *  @see Message
 *  @see BlockAskMessage
 *  @see MessageParser
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class BlockAskParser: public MessageParser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};

#endif //BLOCK_CHAIN_BLOCKASKPARSER_H
