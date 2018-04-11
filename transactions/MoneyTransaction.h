//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_MONEYTRANSACTION_H
#define BLOCK_CHAIN_MONEYTRANSACTION_H


#include "../block_chain/chain/block/transaction/Transaction.h"

class MoneyTransaction: public Transaction {
public:
    explicit MoneyTransaction();
    explicit MoneyTransaction(int a, std::string str);
    bool operator()() const final;
    virtual Element* toElement() const override;
    bool operator==(Transaction* t) const {
        MoneyTransaction* s = dynamic_cast<MoneyTransaction*>(t);
        return amount == s->amount && target == s->target;
    }
    std::string to_string() const;
    std::vector<std::string> apply(Row* row) override;
    virtual Row* createRow() const;
    virtual void apply_reverse(Row* row);
    virtual bool validate(Row *row) const override;
protected:
    virtual void fromElement(ElementObject*, const Serializer*, const char* encoding) override;
private:
    double amount;
    std::string target;
};


#endif //BLOCK_CHAIN_MONEYTRANSACTION_H
