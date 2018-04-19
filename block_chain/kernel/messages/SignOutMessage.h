//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_SIGNOUTMESSAGE_H
#define BLOCK_CHAIN_SIGNOUTMESSAGE_H


#include "SignMessage.h"

class SignOutMessage: public SignMessage {
public:
    SignOutMessage();
    SignOutMessage(std::string p);
};



#endif //BLOCK_CHAIN_SIGNOUTMESSAGE_H
