//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_SIGNOUTMESSAGE_H
#define BLOCK_CHAIN_SIGNOUTMESSAGE_H


#include "SignMessage.h"

/**
 *  @class SignOutMessage "block_chain/kernel/messages/SignOutMessage.h"
 *  An sign out message for signing out of a peer list
 *  @see SignMessage
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class SignOutMessage: public SignMessage {
public:
    SignOutMessage();

    /**
     *  Creates a sign out message with a text and
     *  a message type
     *  Calls the super constructor with the type value
     *  @see Message::SIGN_OUT
     *
     *  @param p The users's peer representation
     */
    SignOutMessage(std::string p);
};



#endif //BLOCK_CHAIN_SIGNOUTMESSAGE_H
