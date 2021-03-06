//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_PEERSANSWERPARSER_H
#define BLOCK_CHAIN_PEERSANSWERPARSER_H


#include "MessageParser.h"

/**
 *  @class PeersAnswerParser "block_chain/kernel/parsers/PeersAnswerParser.h"
 *  A message parser linked to a AnswerPeersMessage.
 *  @see Message
 *  @see AnswerPeersMessage
 *  @see MessageParser
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class PeersAnswerParser: public MessageParser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};


#endif //BLOCK_CHAIN_PEERSANSWERPARSER_H
