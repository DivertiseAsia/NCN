//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKASKMESSAGE_H
#define BLOCK_CHAIN_BLOCKASKMESSAGE_H


#include "Message.h"

class BlockAskMessage: public Message
{
    friend class BlockAskParser;
public:
    BlockAskMessage();
    BlockAskMessage(std::string b, std::string f);
    ~BlockAskMessage() override;
    Element* toElement() const override;
protected:
    void fromElement(ElementObject*, const Serializer* serializer, const char* encoding) override;

private:
    std::string block;
    std::string fingerprint;
};

#endif //BLOCK_CHAIN_BLOCKASKMESSAGE_H
