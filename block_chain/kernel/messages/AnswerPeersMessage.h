//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_ANSWERPEERSMESSAGE_H
#define BLOCK_CHAIN_ANSWERPEERSMESSAGE_H


#include "SignMessage.h"

class AnswerPeersMessage: public SignMessage {
public:
    AnswerPeersMessage();
    AnswerPeersMessage(std::string p);
};


#endif //BLOCK_CHAIN_ANSWERPEERSMESSAGE_H
