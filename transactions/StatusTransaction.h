//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_STATUS_TRANSACTION_H
#define BLOCK_CHAIN_STATUS_TRANSACTION_H

#include <string>
#include "../block_chain/chain/block/transaction/Transaction.h"
#include <iostream>
#include "../database/Row.h"
#include "../block_chain/chain/Row.h"

class StatusTransaction: public Transaction {
public:
    explicit StatusTransaction();
    bool operator()() const final;
    Element* toElement() const override;
    bool operator==(Transaction* t) const override {
        auto * s = dynamic_cast<StatusTransaction*>(t);
        return status == s->status;
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
    std::string status;
};


#endif //BLOCK_CHAIN_STATUS_TRANSACTION_H
