//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_PEERSASKPARSER_H
#define BLOCK_CHAIN_PEERSASKPARSER_H


#include "MessageParser.h"

/**
 *  @class PeersAskParser "block_chain/kernel/parsers/PeersAskParser.h"
 *  A message parser linked to a AskPeersMessage.
 *  @see Message
 *  @see AskPeersMessage
 *  @see MessageParser
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class PeersAskParser: public MessageParser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};

#endif //BLOCK_CHAIN_PEERSASKPARSER_H
