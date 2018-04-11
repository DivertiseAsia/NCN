//
// Created by default on 10/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTIONCONTAINER_H
#define BLOCK_CHAIN_TRANSACTIONCONTAINER_H

#include "Transaction.h"
#include "../Component.h"

class TransactionContainer:public Component {
public:
    TransactionContainer(Transaction* tr, std::string t, std::string c, std::string p, Serializer* serializer, const char* encoding);
    explicit TransactionContainer();
    virtual Element* toElement() const;
    virtual std::string to_string() const;
    void __hash__(const Serializer* serializer, const char* encoding);
    virtual bool operator()() const;
    virtual bool operator==(TransactionContainer* s) const {
        return this->transaction == s->transaction && hash == s->hash;
    }
    Hash* hash;
    Transaction* transaction;
    std::string transac;
protected:
    virtual void fromElement(ElementObject*, const Serializer* serializer, const char* encoding);
private:
    std::string public_key;
    std::string cipher;
};


#endif //BLOCK_CHAIN_TRANSACTIONCONTAINER_H
