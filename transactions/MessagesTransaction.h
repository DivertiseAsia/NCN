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
    virtual Element* toElement() const override;
    bool operator==(Transaction* t) const {
        MessagesTransaction* s = dynamic_cast<MessagesTransaction*>(t);
        return message == s->message;
    }
    std::string to_string() const;
    void apply() override;
protected:
    virtual void fromElement(ElementObject*, const Serializer*, const char* encoding) override;
private:
    std::string message;
};


#endif //BLOCK_CHAIN_MESSAGES_TRANSACTION_H
