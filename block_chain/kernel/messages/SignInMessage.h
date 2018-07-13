//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_SIGNINMESSAGE_H
#define BLOCK_CHAIN_SIGNINMESSAGE_H


#include "SignMessage.h"

/**
 *  @class SignInMessage "block_chain/kernel/messages/SignInMessage.h"
 *  An sign in message for signing out of a peer list
 *  @see SignMessage
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class SignInMessage: public SignMessage {
public:
    SignInMessage();

    /**
     *  Creates a sign in message with a text
     *  Calls the super constructor with the type value
     *  @see Message::SIGN_IN
     *
     *  @param p The users's peer representation
     */
    explicit SignInMessage(std::string p);
};


#endif //BLOCK_CHAIN_SIGNINMESSAGE_H
