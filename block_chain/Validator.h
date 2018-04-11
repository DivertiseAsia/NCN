//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_VALIDATOR_H
#define BLOCK_CHAIN_VALIDATOR_H

#include "chain/block/transaction/Transaction.h"
#include "chain/block/Block.h"

class Validator {
public:
    Validator(const Serializer* s, const char* e);
    bool operator()(Transaction* transaction);
    bool operator()(TransactionContainer* transaction);
    virtual bool operator()(Block* block);
    virtual ~Validator();
private:
    const Serializer* serializer;
    const char* encoding;
};


#endif //BLOCK_CHAIN_VALIDATOR_H
