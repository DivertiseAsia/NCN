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

class Block: public Component{
    friend class NodeState;
public:
    Block();
    explicit Block(std::vector<Transaction*> transactions);
    virtual Element* toElement();
    virtual ~Block();
    bool operator==(Block* block) const{
        return data == block->data && fingerprint == block->fingerprint && parent_fingerprint == block->parent_fingerprint;
    }
protected:
    virtual void fromElement(ElementObject* e) override;
private:
    Metadata data;
    Hash* fingerprint;
    Hash* parent_fingerprint;
};
#endif //BLOCK_CHAIN_BLOCK_H
