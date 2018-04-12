//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_MESSAGES_TRANSACTION_H
#define BLOCK_CHAIN_MESSAGES_TRANSACTION_H

#include <string>
#include <cstdlib>
#include "../block_chain/chain/block/transaction/Transaction.h"
#include "../database/Row.h"

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
    std::vector<std::string> apply(Row* row) override;
    virtual Row* createRow() const;
    virtual void apply_reverse(Row* row);
    virtual bool validate(Row *row) const override;
    int get_type() const override;
    virtual std::string description() const;
    virtual void fill_data();
    virtual Transaction* clone();
protected:
    virtual void fromElement(ElementObject*, const Serializer*, const char* encoding) override;
private:
    std::string message;
};


#endif //BLOCK_CHAIN_MESSAGES_TRANSACTION_H
