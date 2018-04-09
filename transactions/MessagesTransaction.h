//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_MESSAGES_TRANSACTION_H
#define BLOCK_CHAIN_MESSAGES_TRANSACTION_H

#include <string>
#include <cstdlib>
#include "../block_chain/chain/block/transaction/Transaction.h"

class MessagesTransaction: public Transaction {
public:
    explicit MessagesTransaction();
    explicit MessagesTransaction(std::string str);
    bool operator()() const final;
    virtual Element* toElement() final;
protected:
    virtual void fromElement(ElementObject*) final;
private:
    std::string message;
};


#endif //BLOCK_CHAIN_MESSAGES_TRANSACTION_H
