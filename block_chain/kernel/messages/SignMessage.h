//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_SIGNMESSAGE_H
#define BLOCK_CHAIN_SIGNMESSAGE_H


#include "Message.h"

class SignMessage: public Message
{
    friend class SignInParser;
    friend class SignOutParser;
    friend class PeersAskParser;
    friend class PeersAnswerParser;
public:
    SignMessage();
    SignMessage(std::string p, int t);
    ~SignMessage() override;
    Element* toElement() const override;
protected:
    void fromElement(ElementObject*, const Serializer* serializer, const char* encoding) override;

private:
    std::string peer;
};


#endif //BLOCK_CHAIN_SIGNMESSAGE_H
