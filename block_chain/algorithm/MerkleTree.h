//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_MERKLE_TREE_H
#define BLOCK_CHAIN_MERKLE_TREE_H

#include "Hash.h"
#include "../chain/block/transaction/Transaction.h"

class Block;

/**
 *  @class MerkleTree "block_chain/algorithm/MerkleTree.h"
 *  The Merkle tree representation for Hashes
 *  in a Block
 *  @see Block
 *  @see Hash
 *  @see Transaction
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class MerkleTree: public Component {
public:
    friend class Node;
    friend class Message;
    friend class TransactionMessage;
    friend class TransactionParser;
    friend class BlockMessage;

    /**
     *  Generates the tree of a single transaction
     *
     *  @param transaction The transaction to put in the tree
     *  @param serializer The serializer to serialize the component
     *  @param encoding The encoding to serialize the component
     */
    MerkleTree(Transaction* transaction, const Serializer* serializer, const char* encoding);
    /**
     *  Generates the tree of a single transaction
     *
     *  @param block The block to put in the tree
     *  @param serializer The serializer to serialize the component
     *  @param encoding The encoding to serialize the component
     */
    MerkleTree(Block* block, const Serializer* serializer, const char* encoding);

    /**
     *  Generates the tree of a list of transactions
     *
     *  @param transactions The list of transactions to put in the tree
     *  @param serializer The serializer to serialize the component
     *  @param encoding The encoding to serialize the component
     */
    MerkleTree(std::vector<Transaction*> transactions, const Serializer* serializer, const char* encoding);

    /**
     *  Generates the tree based of nodes
     *
     *  @param l The left tree
     *  @param r The right tree
     */
    MerkleTree(MerkleTree* l, MerkleTree* r);

    /**
     *  A destructor that destroy its own hash value
     *  and then both left and right trees
     */
    ~MerkleTree() override;
    Element* toElement() const override;

    /**
     *  Get the Hash of a given element
     *
     *  @param i The index of the given element
     *  @return The hash of the asked index
     */
    Hash* get_hash(int i) const;

    /**
     *  Get the number of Hashes in the tree
     *
     *  @return The number of Hashes in the tree
     */
    int size() const;

    /**
     *  Generates the tree for a given list of transactions
     *  @see Hash
     *  @see Serializer
     *
     *  @param transactions The list of transactions to hash
     *  @param begin The first index of the array
     *  @param end The last index of the array
     *  @param serializer The serializer
     *  @param encoding The encoding that has been used to create the Element representation of the object
     */
    void generate_tree(std::vector<Transaction*> transactions, int begin, int end, const Serializer* serializer, const char* encoding);

    /**
     *  A default Merkle tree constructor
     */
    MerkleTree();

protected:
    void fromElement(ElementObject*, const Serializer*, const char* encoding) override;
private:

    /**
     *  The Merkle tree on the left
     */
    MerkleTree* left;

    /**
     *  The Merkle tree on the right
     */
    MerkleTree* right;

    /**
     *  The hash value of the MerkleTree node
     */
    Hash* value;
};


#endif //BLOCK_CHAIN_MERKLE_TREE_H
