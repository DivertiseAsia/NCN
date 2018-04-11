//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTION_H
#define BLOCK_CHAIN_TRANSACTION_H
#include "../Component.h"
#include "../Hash.h"

class Serializer;
class Transaction: public Component {
    friend class TransactionContainer;
public:
    virtual bool operator()() const = 0;
    virtual bool operator==(Transaction* s) const = 0;
    Hash* __hash__(const Serializer* serializer, const char* encoding) const;
    virtual void apply() = 0;
};


#endif //BLOCK_CHAIN_TRANSACTION_H
