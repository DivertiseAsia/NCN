//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCK_H
#define BLOCK_CHAIN_BLOCK_H

#include <vector>
#include "../../algorithm/Hash.h"
#include "proof/metadata/Metadata.h"
#include "../../kernel/components/Component.h"
#include "../../algorithm/MerkleTree.h"
#include <iostream>
#include <chrono>

class Serializer;

/**
 *  @class Block "block_chain/chain/block/Block.h"
 *  The block is one of the most important element
 *  of the block chain.
 *
 *  @author Mathieu Lochet
 *  @version 4
 */
class Block: public Component{
    friend class MerkleTree;
    friend class NodeState;
    friend class Node;
    friend class ProofOfWork;
    friend class Chain;
    friend class TransactionParser;
    friend class BlockParser;
public:
    /**
     *  A default constructor to initialize pointers
     */
    Block();

    /**
     *  Create a Block with a given parent's fingerprint and list of transactions
     *  @see Hash
     *
     *  @param transactions list of transactions contained into the block
     *  @param h Parent's fingerprint
     */
    explicit Block(std::vector<std::pair<std::string, std::string>> transactions, Hash* h);
    Element* toElement() const override;

    /**
     *  A destructor that deletes the block field
     *  that are only linked to that block:
     *  - fingerprint
     *  - data
     */
    ~Block() override;

    /**
     *  Check if two blocks are identical
     *
     *  @param block The block to compare to
     *  @return true if they are the same, false otherwise
     */
    bool operator==(Block* block) const{
        return data == block->data && *fingerprint == *block->fingerprint && *parent_fingerprint == *block->parent_fingerprint;
    }

    /**
     *  Generates the block's fingerprint
     *  @see Hash
     *  @see Serializer
     *
     *  @param s The serializer
     *  @param e The encoding that has been used to create the Element representation of the object
     *  @return The computed Hash of the array
     */
    Hash* compute_fingerprint(const Serializer* s, const char* e) const;

    /**
     *  Check if the given fingerprint is the same than the newly computed fingerprint
     *  @see Hash
     *  @see Serializer
     *
     *  @param s The serializer
     *  @param e The encoding that has been used to create the Element representation of the object
     *  @return true if both fingerprints are the same, false otherwise
     */
    bool checkFingerPrint(const Serializer* s, const char* e) const;

    /**
     *  Update the block's fingerprint
     *
     *  @param s The serializer
     *  @param e The encoding that has been used to create the Element representation of the object
     */
    void update_fingerprint(const Serializer* s, const char* e);
protected:
    void fromElement(ElementObject* e, const Serializer* s, const char* encoding) override;
private:

    /**
     *  The timestamp at which the block has been created
     */
    long long int timestamp;

    /**
     *  The header data of the block, for proof validation
     */
    Metadata* data;

    /**
     *  The list of transaction is a list of pairs
     *  Theses pairs are composed by:
     *  - the key of the transaction creator
     *  - The serialized and ciphered transaction
     */
    std::vector<std::pair<std::string, std::string>> transactions;

    /**
     *  The fingerprint of the block
     */
    Hash* fingerprint;

    /**
     *  The fingerprint of the parent's block
     */
    Hash* parent_fingerprint;

    /**
     *  The method that will generate the Hash with the list
     *  of transactions
     *  @see Hash
     *  @see Serializer
     *
     *  @param begin The first index of the array
     *  @param end The last index of the array
     *  @param s The serializer
     *  @param e The encoding that has been used to create the Element representation of the object
     *  @return The computed Hash of the array
     */
    Hash* compute_hash(int begin, int end, const Serializer* s, const char* e) const;
};
#endif //BLOCK_CHAIN_BLOCK_H
