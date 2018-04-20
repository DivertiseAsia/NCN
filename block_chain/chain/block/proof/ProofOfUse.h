//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOF_OF_USE_H
#define BLOCK_CHAIN_PROOF_OF_USE_H


#include "Proof.h"

/**
 *  A basic proof of use
 *  @see Proof
 *  @see Proof::USE
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ProofOfUse: public Proof {
public:
    void run(Block* block, std::string key) override;
    bool accept(Block* block, Message* message) override;
};


#endif //BLOCK_CHAIN_PROOF_OF_USE_H
