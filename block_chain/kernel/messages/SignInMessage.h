//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_SIGNINMESSAGE_H
#define BLOCK_CHAIN_SIGNINMESSAGE_H


#include "SignMessage.h"

class SignInMessage: public SignMessage {
public:
    SignInMessage();
    SignInMessage(std::string p);
};


#endif //BLOCK_CHAIN_SIGNINMESSAGE_H
