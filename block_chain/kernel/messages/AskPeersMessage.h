//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_ASKPEERSMESSAGE_H
#define BLOCK_CHAIN_ASKPEERSMESSAGE_H


#include "SignMessage.h"

/**
 *  An ask peers message for asking the peers list
 *  @see SignMessage
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class AskPeersMessage: public SignMessage {
public:
    AskPeersMessage();

    /**
     *  Creates a ask peers message with a text
     *  Calls the super constructor with the type value
     *  @see Message::ASK_PEERS
     *
     *  @param p The users's peer representation
     */
    AskPeersMessage(std::string p);
};

#endif //BLOCK_CHAIN_ASKPEERSMESSAGE_H
