//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKMESSAGE_H
#define BLOCK_CHAIN_BLOCKMESSAGE_H


#include "Message.h"

class BlockMessage: public Message
{
    friend class BlockParser;
public:
    BlockMessage();
    BlockMessage(std::string b, std::string k, MerkleTree* tr);
    ~BlockMessage() override;
    Element* toElement() const override;
    const std::string get_key() const;
protected:
    void fromElement(ElementObject*, const Serializer* serializer, const char* encoding) override;

private:
    std::string block;
    std::string key;
    MerkleTree* tree;
};


#endif //BLOCK_CHAIN_BLOCKMESSAGE_H
