//
// Created by default on 17/4/2561.
//

#ifndef BLOCK_CHAIN_CHAIN_H
#define BLOCK_CHAIN_CHAIN_H


#include <vector>
#include "../algorithm/Hash.h"
#include "block/Block.h"
#include "state/Database.h"
#include "../utils/serialization/Serializer.h"

/**
 *  @class Chain "block_chain/chain/Chain.h"
 *  The chain contains all of the blocks and
 *  builds the block chain. It also updates the
 *  current state of a system with temporal
 *  databases.
 *  @see Database
 *  @see Block
 *  @see Hash
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class Chain {
    friend class NodeState;
public:

    /**
     *  Creates a new Chain, with a parent Chain and a corresponding block
     *  @see Block
     *
     *  @param b The new Block to add on the chain
     *  @param cr The creator of the string
     *  @param c The parent Chain
     */
    Chain(Block* b, Chain* c, std::string cr);

    /**
     *  Creates the root chain, with a given Reward object
     *
     *  @param r The reward object used to update the database when a block is added
     */
    explicit Chain(const Reward* r);

    /**
     *  A destructor which destroy all of the child and database
     */
    ~Chain();

    /**
     *  Add a new block on the chain, and links it with its parent's fingerprint
     *
     *  @param block The new Block to add on the chain
     *  @param creator The creator of the string
     *  @return the newly created chain
     */
    Chain * add(Block* block, std::string creator);

    /**
     *  Get the top chain in the block chain
     *
     *  @return A pair containing both the depth of the top chain, and the chain itself
     */
    std::pair<int, Chain*> top_fingerprint();

    /**
     *  Update the chain database with a given block.
     *  The method will apply all of the transactions to the database
     *
     *  @param b The block to use for update
     *  @param s The serializer
     *  @param encoding The encoding that has been used to create the Element representation of the object
     */
    void update_database(Block* b, const Serializer* s, const char* encoding);

    /**
     *  Check if the transaction can be applied in a new block
     *  @see Transaction
     *
     *  @param transaction the transaction to check
     *  @param k The identifier ot the user in the database
     *  @return true if it can be applied, false otherwise
     */
    bool check_transaction(Transaction* transaction, std::string k);

    /**
     *  Count the number of blocks in totalm including the ones on forks
     *
     *  @return The number of blocks in the Chain
     */
    int count() const;

    /**
     *  Get the original creator of the block
     *
     *  @param hash The fingerprint of the block
     *  @return The creator of the block
     */
    std::string find_creator(std::string &hash);
private:

    /**
     *  The database representing this block of the block chain
     */
    Database database;

    /**
     *  The fingerprint of the block
     */
    Hash* fingerprint;

    /**
     *  The list of possible following chain
     */
    std::vector<Chain*> chain;

    /**
     *  Print the current database
     */
    void show();

    /**
     *  Try to find a given hash in the database
     *  @see Hash
     *
     *  @return 1 if the fingerprint has been found, 0 otherwise
     */
    int find(Hash *pHash);

    /**
     *  Try to find a given hash in the database
     *
     *  @return The corresponding block if it is found, nullptr otherwise
     */
    Block * find(std::string str);

    /**
     *  The corresponding block
     */
    Block *block;

    /**
     *  The creator of the block
     */
     std::string creator;
};




#endif //BLOCK_CHAIN_CHAIN_H
