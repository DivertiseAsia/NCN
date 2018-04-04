//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_STATUSTRANSACTION_H
#define BLOCK_CHAIN_STATUSTRANSACTION_H

#include <string>
#include "../block_chain/chain/block/transaction/Transaction.h"

class StatusTransaction: public Transaction {
public:
    StatusTransaction(std::string str);
    virtual bool operator()() const;
private:
    std::string status;
};


#endif //BLOCK_CHAIN_STATUSTRANSACTION_H
