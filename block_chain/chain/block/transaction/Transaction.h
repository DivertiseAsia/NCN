//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTION_H
#define BLOCK_CHAIN_TRANSACTION_H
#include "../Component.h"
#include "../Hash.h"

class Serializer;
class Transaction: public Component {
    friend class Block;
public:
    virtual bool operator()() const = 0;
    virtual bool operator==(Transaction* s) const = 0;
    void __hash__(Serializer* serializer, const char* encoding);

protected:
    Hash* hash;
};


#endif //BLOCK_CHAIN_TRANSACTION_H
