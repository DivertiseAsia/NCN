//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_STATUS_TRANSACTION_H
#define BLOCK_CHAIN_STATUS_TRANSACTION_H

#include <string>
#include "../block_chain/chain/block/transaction/Transaction.h"

class StatusTransaction: public Transaction {
public:
    explicit StatusTransaction(std::string str);
    bool operator()() const final;
    virtual char* serialize() const final;
private:
    std::string status;
};


#endif //BLOCK_CHAIN_STATUS_TRANSACTION_H
