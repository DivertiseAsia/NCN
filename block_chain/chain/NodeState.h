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
#ifndef _WIN32
#include <sys/stat.h>
#else
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#endif // _WIN32
#include <dirent.h>
#include <algorithm>
#include <utility>
#include "block/Block.h"
#include "state/Database.h"
#include "Chain.h"
#include "../algorithm/hash/Hash_MD5.h"
#include "../algorithm/cryptography/RSA.h"
#include "../utils/serialization/Serializer.h"
#include "../utils/socket/Peer.h"

/**
 *  @class NodeState "block_chain/chain/NodeState.h"
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
    explicit NodeState(const Serializer* s, int si = 64, const char* e = "json", const Reward* r = nullptr);

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
     *  @param creator the creator of the block
     *  @param crypto The cryptography index to use
     */
    void add(Block* block, std::string creator, int crypto);

    /**
     *  Read all of the block files and memorize all of it
     *
     *  @param crypto The cryptography index to use
     */
    void read_blocks(int crypto);

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
     *
     *  @return The corresponding block if it is found, nullptr otherwise
     */
    Block *get(std::string& hash);


    /**
     *  Get the original creator of the block
     *
     *  @param hash The fingerprint of the block
     *  @return The creator of the block
     */
    std::string get_creator(std::string& hash);

private:

    /**
     *  The serializer
     */
    const Serializer* serializer;

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

};
#endif //BLOCK_NODE_STATE_CHAIN_H
