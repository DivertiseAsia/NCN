//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTION_H
#define BLOCK_CHAIN_TRANSACTION_H


class Transaction {
public:
    virtual bool operator()() const = 0;
    virtual char* serialize() const = 0;
private:
};


#endif //BLOCK_CHAIN_TRANSACTION_H
