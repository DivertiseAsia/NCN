//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFHOLD_H
#define BLOCK_CHAIN_PROOFOFHOLD_H


#include "Proof.h"

/**
 *  @class ProofOfHold "block_chain/chain/block/proof/ProofOfHold.h"
 *  A basic proof of hold
 *  @see Proof
 *  @see Proof::HOLD
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ProofOfHold: public Proof {
public:
    void run(Block* block, std::string key) const override;
    bool accept(Block* block, Message* message) const override;
};


#endif //BLOCK_CHAIN_PROOFOFHOLD_H
