//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCK_H
#define BLOCK_CHAIN_BLOCK_H

#include <vector>
#include "Hash.h"
#include "Metadata.h"
#include "transaction/Transaction.h"
#include "Component.h"

class Serializer;
class Block: public Component{
    friend class NodeState;
public:
    Block(const Serializer*, const char*);
    explicit Block(std::vector<Transaction*> transactions, Hash*);
    virtual Element* toElement();
    virtual ~Block();
    bool operator==(Block* block) const{
        return data == block->data && fingerprint == block->fingerprint && parent_fingerprint == block->parent_fingerprint;
    }
    Hash* compute_fingerprint() const;
    bool checkFingerPrint() const;
protected:
    virtual void fromElement(ElementObject* e) override;
private:
    const Serializer* serializer;
    const char* encoding;
    Metadata data;
    std::vector<Transaction*> transactions;
    Hash* fingerprint;
    Hash* parent_fingerprint;
    Hash* compute_hash(int begin, int end) const;
};
#endif //BLOCK_CHAIN_BLOCK_H
