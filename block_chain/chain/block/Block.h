//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCK_H
#define BLOCK_CHAIN_BLOCK_H

#include <vector>
#include "../../algorithm/Hash.h"
#include "proof/metadatas/Metadata.h"
#include "../../kernel/components/Component.h"
#include <iostream>
#include <chrono>

class Serializer;

class Block: public Component{
    friend class NodeState;
    friend class Node;
    friend class ProofOfWork;
    friend class Chain;
    friend class TransactionParser;
    friend class BlockParser;
public:
    Block(const Serializer*, const char*);
    explicit Block(std::vector<std::pair<std::string, std::string>> transactions, Hash*, const Serializer* s, const char* e);
    Element* toElement() const override;
    ~Block() override;
    bool operator==(Block* block) const{
        return data == block->data && *fingerprint == *block->fingerprint && *parent_fingerprint == *block->parent_fingerprint;
    }
    Hash* compute_fingerprint(const Serializer* s, const char* e) const;
    bool checkFingerPrint(const Serializer* s, const char* e) const;
    virtual std::string to_string() const;
    void update_fingerprint();
protected:
    void fromElement(ElementObject* e, const Serializer* s, const char* encoding) override;
private:
    long long int timestamp;
    const Serializer* serializer;
    const char* encoding;
    Metadata* data;
    std::vector<std::pair<std::string, std::string>> transactions;
    Hash* fingerprint;
    Hash* parent_fingerprint;
    Hash* compute_hash(int begin, int end, const Serializer* s, const char* e) const;
};
#endif //BLOCK_CHAIN_BLOCK_H
