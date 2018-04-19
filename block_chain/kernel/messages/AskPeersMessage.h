//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_ASKPEERSMESSAGE_H
#define BLOCK_CHAIN_ASKPEERSMESSAGE_H


#include "SignMessage.h"

class AskPeersMessage: public SignMessage {
public:
    AskPeersMessage();
    AskPeersMessage(std::string p);
};

#endif //BLOCK_CHAIN_ASKPEERSMESSAGE_H
