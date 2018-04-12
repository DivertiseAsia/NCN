//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_SERIALIZER_H
#define BLOCK_CHAIN_SERIALIZER_H

#include "chain/block/Block.h"
#include "chain/block/transaction/Transaction.h"
#include "utils/Factory.hpp"
#include "utils/serialization/Parser.hpp"
#include "Message.h"
#include <cstdlib>

class Serializer
{
public:
    Serializer();
    virtual char* serialize(const Component* component, const char* key) const;
    virtual char* serialize(Element* element, const char* key) const;
    virtual TransactionContainer* unserializeTransactionContainer(std::string message, const char* key) const;
    virtual Transaction* unserializeTransaction(std::string transaction, const char* key) const;
    virtual Block* unserializeBlock(std::string block, const char* key) const;
    virtual Message* unserializeMessage(std::string message, const char* key) const;
    ElementObject* getElement(std::string transaction, const char* key) const;
    void set_serializer(const char* key, ContentCreator* creator);
    void set_unserializer(const char* key, ContentParser* parser);
protected:
    Factory<ContentCreator*> creators;
    Factory<ContentParser*> parsers;
};


#endif //BLOCK_CHAIN_SERIALIZER_H
