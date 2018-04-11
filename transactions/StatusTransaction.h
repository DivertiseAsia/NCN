//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_STATUS_TRANSACTION_H
#define BLOCK_CHAIN_STATUS_TRANSACTION_H

#include <string>
#include "../block_chain/chain/block/transaction/Transaction.h"
#include <iostream>

class StatusTransaction: public Transaction {
public:
    explicit StatusTransaction();
    explicit StatusTransaction(std::string str);
    bool operator()() const final;
    virtual Element* toElement() const override;
    bool operator==(Transaction* t) const {
        StatusTransaction* s = dynamic_cast<StatusTransaction*>(t);
        return status == s->status;
    }
    std::string to_string() const;
    void apply() override;
protected:
    virtual void fromElement(ElementObject*, const Serializer*, const char* encoding) override;
private:
    std::string status;
};


#endif //BLOCK_CHAIN_STATUS_TRANSACTION_H
