//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFSTAKE_H
#define BLOCK_CHAIN_PROOFOFSTAKE_H


#include "Proof.h"

/**
 *  @class ProofOfStake "block_chain/chain/block/proof/ProofOfStake.h"
 *  A basic proof of stake
 *  @see Proof
 *  @see Proof::STAKE
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ProofOfStake: public Proof {
public:
    void run(Block* block, std::string key) const override;
    bool accept(Block* block, Message* message) const override;
};

#endif //BLOCK_CHAIN_PROOFOFSTAKE_H
