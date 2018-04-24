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
 *  @class Proof "block_chain/chain/block/proof/Proof.h"
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

    /**
     *  The constant corresponding to the proof of work
     */
    static const int WORK;

    /**
     *  The constant corresponding to the proof of stake
     */
    static const int STAKE;

    /**
     *  The constant corresponding to the proof of hold
     */
    static const int HOLD;

    /**
     *  The constant corresponding to the proof of importance
     */
    static const int IMPORTANCE;

    /**
     *  The constant corresponding to the proof of minimum aged stake
     */
    static const int MINIMUM_AGED_STAKE;

    /**
     *  The constant corresponding to the proof of stake over time
     */
    static const int STAKE_TIME;

    /**
     *  The constant corresponding to the proof of use
     */
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
     *  @param type The proof id
     *  @return The created proof object
     */
    static Proof* generate(int type);

    /**
     *  Run a proof on a block to validate it
     *  Needs to be implemented
     *
     *  @param block The block to run the proof on
     *  @param key The user's key to use in the process
     */
    virtual void run(Block* block, std::string key) const = 0;

    /**
     *  Get a proof result and check if the result is correct
     *  Needs to be implemented
     *
     *  @param block The block to check the proof
     *  @param message The received message
     */
    virtual bool accept(Block* block, Message* message) const = 0;

    /**
     * Default destructor
     */
     virtual ~Proof() = default;
private:

    /**
     *  The list of all known proofs
     */
    static std::map<int, std::function<Proof*()>> items;
};


#endif //BLOCK_CHAIN_PROOF_H
