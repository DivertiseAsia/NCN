//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_MERKLE_TREE_H
#define BLOCK_CHAIN_MERKLE_TREE_H

#include "../Hash.h"
#include "Transaction.h"

class MerkleTree: public Component {
public:
    friend class Node;
    friend class Message;
    MerkleTree(Transaction* transaction, const Serializer* serializer, const char* encoding);
    MerkleTree(std::vector<Transaction*> transactions, const Serializer* serializer, const char* encoding);
    MerkleTree(MerkleTree* l, MerkleTree* r);
    ~MerkleTree();
    Element* toElement() const override;
    Hash* get_hash(const int i) const;
    int size() const;
    void generate_tree(std::vector<Transaction*> transactions, int begin, int end, const Serializer* serializer, const char* encoding);
protected:
    virtual void fromElement(ElementObject*, const Serializer*, const char* encoding);
private:
    MerkleTree();
    MerkleTree* left;
    MerkleTree* right;
    Hash* value;
};


#endif //BLOCK_CHAIN_MERKLE_TREE_H
