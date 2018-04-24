//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFMINIMUMAGEDSTAKE_H
#define BLOCK_CHAIN_PROOFOFMINIMUMAGEDSTAKE_H


#include "Proof.h"

/**
 *  A basic proof of minimum aged stake
 *  @see Proof
 *  @see Proof::MINIMUM_AGED_STAKE
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ProofOfMinimumAgedStake: public Proof {
public:
    void run(Block* block, std::string key) const override;
    bool accept(Block* block, Message* message) const override;
};


#endif //BLOCK_CHAIN_PROOFOFMINIMUMAGEDSTAKE_H
