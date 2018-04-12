//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTION_MANAGER_H
#define BLOCK_CHAIN_TRANSACTION_MANAGER_H


#include "chain/block/transaction/Transaction.h"

class TransactionManager {
public:
    TransactionManager();
    ~TransactionManager();
    void put(Transaction* t);
    Transaction* run();
private:
    std::map<int, Transaction*> transactions;
};


#endif //BLOCK_CHAIN_TRANSACTION_MANAGER_H
