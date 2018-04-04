//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_MESSAGESTRANSACTION_H
#define BLOCK_CHAIN_MESSAGESTRANSACTION_H

#include <string>
#include "../block_chain/chain/block/transaction/Transaction.h"

class MessagesTransaction: public Transaction {
public:
    MessagesTransaction(std::string str);
    virtual bool operator()() const;
private:
    std::string message;
};


#endif //BLOCK_CHAIN_MESSAGESTRANSACTION_H
