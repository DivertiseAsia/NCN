//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_SERIALIZER_H
#define BLOCK_CHAIN_SERIALIZER_H

#include "chain/block/Block.h"
#include "chain/block/transaction/Transaction.h"

class Serializer
{
public:
    virtual char* serialize(Transaction* transaction) const;
    virtual char* serialize(Block* block) const;
    virtual char* unserialize(Transaction* transaction) const;
    virtual char* unserialize(Block* block) const;
};


#endif //BLOCK_CHAIN_SERIALIZER_H
