//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_MONEY_TRANSACTION_H
#define BLOCK_CHAIN_MONEY_TRANSACTION_H


#include "../block_chain/chain/block/transaction/Transaction.h"

class MoneyTransaction: public Transaction {
public:
    explicit MoneyTransaction();
    bool operator()() const final;

    Element* toElement() const override;
    bool operator==(Transaction* t) const override {
        auto * s = dynamic_cast<MoneyTransaction*>(t);
        return amount == s->amount && target == s->target;
    }
    std::string to_string() const;
    std::vector<std::string> apply(Row* row) override;

    Row* createRow() const override;

    void apply_reverse(Row* row) override;

    bool validate(Row *row) const override;
    int get_type() const override;

    std::string description() const override;

    void fill_data() override;

    Transaction* clone() override;
protected:
    void fromElement(ElementObject*, const Serializer*, const char* encoding) override;
private:
    double amount;
    std::string target;
};


#endif //BLOCK_CHAIN_MONEY_TRANSACTION_H
