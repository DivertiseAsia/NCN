//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOF_H
#define BLOCK_CHAIN_PROOF_H

#include <map>
#include <functional>
#include "../Block.h"
#include "../../../kernel/messages/Message.h"
#include "../../../kernel/messages/BlockMessage.h"

/**
 *  An abstract proof and a proof factory.
 *  A proof is used to avoid falsification of the block chain
 *  Some proofs are provided and a user can create its own
 *  proofs and add them into the factory.
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class Proof {
public:
    static const int WORK;
    static const int STAKE;
    static const int HOLD;
    static const int IMPORTANCE;
    static const int MINIMUM_AGED_STAKE;
    static const int STAKE_TIME;
    static const int USE;

    /**
     *  Allows the user to add its own proof into the system
     *  He the proof id is required
     *
     *  @param id The proof id
     *  @param proof The lambda expression that creates a proof
     */
    static void add_proof(int id, std::function<Proof*()> proof);

    /**
     *  Generates a proof for a given id
     *
     *  @param id The proof id
     *  @return The created proof object
     */
    static Proof* generate(int type);

    /**
     *  Run a proof on a block to validate it
     *  Needs to be implemented
     *
     *  @param block The block to run the proof on
     *  @param The user's key to use in the process
     */
    virtual void run(Block* block, std::string key) = 0;

    /**
     *  Get a proof result and check if the result is correct
     *  Needs to be implemented
     *
     *  @param block The block to check the proof
     *  @param The received message
     */
    virtual bool accept(Block* block, Message*) = 0;
private:

    /**
     *  The list of all known proofs
     */
    static std::map<int, std::function<Proof*()>> items;
};


#endif //BLOCK_CHAIN_PROOF_H
