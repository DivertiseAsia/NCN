//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKANSWERMESSAGE_H
#define BLOCK_CHAIN_BLOCKANSWERMESSAGE_H


#include "Message.h"

class BlockAnswerMessage: public Message
{
    friend class BlockAnswerParser;
public:
    BlockAnswerMessage();
    BlockAnswerMessage(std::string p);
    ~BlockAnswerMessage() override;
    Element* toElement() const override;
protected:
    void fromElement(ElementObject*, const Serializer* serializer, const char* encoding) override;

private:
    std::string block;
};



#endif //BLOCK_CHAIN_BLOCKANSWERMESSAGE_H
