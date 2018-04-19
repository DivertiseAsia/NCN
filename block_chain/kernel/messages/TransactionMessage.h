//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTIONMESSAGE_H
#define BLOCK_CHAIN_TRANSACTIONMESSAGE_H


#include "Message.h"

class TransactionMessage: public Message
{
    friend class TransactionParser;
public:
    TransactionMessage();
    TransactionMessage(std::string p, std::string c, std::string k, MerkleTree*);
    ~TransactionMessage() override;
    Element* toElement() const override;
    bool compareResults(std::string cipher);
    std::string getCipher();
    std::string to_string() const;
protected:
    void fromElement(ElementObject*, const Serializer* serializer, const char* encoding) override;

private:
    std::string public_key;
    std::string plain_text;
    std::string cipher;
    MerkleTree* tree;
};


#endif //BLOCK_CHAIN_TRANSACTIONMESSAGE_H
