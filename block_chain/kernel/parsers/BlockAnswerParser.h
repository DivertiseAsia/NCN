//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKANSWERPARSER_H
#define BLOCK_CHAIN_BLOCKANSWERPARSER_H


#include "MessageParser.h"

/**
 *  @class BlockAnswerParser "block_chain/kernel/parsers/BlockAnswerParser.h"
 *  A message parser linked to a BlockAnswerMessage.
 *  @see Message
 *  @see BlockAnswerMessage
 *  @see MessageParser
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class BlockAnswerParser: public MessageParser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};


#endif //BLOCK_CHAIN_BLOCKANSWERPARSER_H
