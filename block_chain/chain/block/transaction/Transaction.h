//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTION_H
#define BLOCK_CHAIN_TRANSACTION_H
#include "../Component.h"
#include "../Hash.h"
#include "../../Row.h"

class Serializer;
class Transaction: public Component {
    friend class TransactionContainer;
public:
    virtual bool operator()() const = 0;
    virtual bool operator==(Transaction* s) const = 0;
    Hash* __hash__(const Serializer* serializer, const char* encoding) const;
    virtual std::vector<std::string> apply(Row* row) = 0;
    virtual void apply_reverse(Row* row) = 0;
    virtual Row* createRow() const = 0;
    virtual bool validate(Row *row) const = 0;
};


#endif //BLOCK_CHAIN_TRANSACTION_H
