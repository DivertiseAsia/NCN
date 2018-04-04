//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_VALIDATOR_H
#define BLOCK_CHAIN_VALIDATOR_H

#include "chain/block/transaction/Transaction.h"
#include "chain/block/Block.h"

class Validator {
public:
    Validator();
    bool operator()(Transaction* transaction);
    virtual bool operator()(Block* block);
};


#endif //BLOCK_CHAIN_VALIDATOR_H
