//
// Created by default on 3/4/2561.
//
#ifndef BLOCK_NODE_STATE_CHAIN_H
#define BLOCK_NODE_STATE_CHAIN_H

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>
#include <algorithm>
#include <utility>
#include "block/Block.h"
#include "state/Database.h"
#include "Chain.h"
#include "../algorithm/Hash.h"
#include "../algorithm/RSA.h"
#include "../utils/serialization/Serializer.h"
#include "../utils/socket/Peer.h"

/**
 *  The NodeState class contains all the data at a time T.
 *  It is in charge of block generation and validation
 *  builds the block chain. It also updates the
 *  current state of a system with temporal
 *  databases.
 *  @see Serializer
 *  @see Chain
 *  @see Hash
 *  @see Transaction
 *  @see Block
 *
 *  @author Mathieu Lochet
 *  @version 5
 */
class NodeState{
public:
    /**
     *  Creates a new NodeState object with a root chain
     *  a base reward transaction and a size for block
     *  generation
     *  @see Serializer
     *
     *  @param s The used serializer
     *  @param si The size of a block
     *  @param e The used encoding
     *  @param r The reward object
     */
    explicit NodeState(Serializer* s, int si = 64, const char* e = "json", Reward* r = nullptr);

    /**
     *  Creates a block using the stored transactions
     *  @see Block
     *
     *  @return the newly created Block
     */
    Block* create_block() const;

    /**
     *  Add a transaction. If the number of transaction
     *  is equal to the size field, then a new Block
     *  is created
     *  @see Block
     *
     *  @param transaction The serialized and ciphered serialization
     *  @param public_key The key to decipher the transaction
     *  @return A new Block is the number of transactions equals the size field, nullptr otherwise
     */
    Block* add(std::string transaction, std::string public_key);

    /**
     *  Add a new Block to the chain and generate the
     *  file.
     *  @see Block
     *
     *  @param block the block to add to the block chain
     */
    void add(Block* block);

    /**
     *  Read all of the block files and memorize all of it
     */
    void read_blocks();

    /**
     *  Check if a transaction is valid or not
     *
     *  @param transaction The transaction to check
     *  @param k The key of the transaction's creator
     *  @return true if it is valid, false otherwise
     */
    bool check_transaction(Transaction * transaction, std::string k);

    /**
     *  Print the state of the top chain
     */
    void show_current_state();

    /**
     *  Try to find a given hash in the database
     *  @see Hash
     *
     *  @return 1 if the fingerprint has been found, 0 otherwise
     */
    bool get(Hash *pHash);

    /**
     *  Try to find a given hash in the database
     *
     *  @return The corresponding block if it is found, nullptr otherwise
     */
    Block *get(std::string& hash);
private:

    /**
     *  The chosen encoding for serialization
     */
    std::string encoding;

    /**
     *  The number of transaction in one block
     */
    unsigned int size;

    /**
     *  The root chain of the block chain
     */
    Chain* chain;

    /**
     *  The list of transaction is a list of pairs
     *  Theses pairs are composed by:
     *  - the key of the transaction creator
     *  - The serialized and ciphered transaction
     */
    std::vector<std::pair<std::string, std::string>>  transactions;

    /**
     *  The serializer
     */
    Serializer* serializer;

};
#endif //BLOCK_NODE_STATE_CHAIN_H
