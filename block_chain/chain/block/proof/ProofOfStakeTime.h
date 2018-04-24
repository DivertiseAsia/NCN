//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFSTAKETIME_H
#define BLOCK_CHAIN_PROOFOFSTAKETIME_H


#include "Proof.h"

/**
 *  A basic proof of stake over time
 *  @see Proof
 *  @see Proof::STAKE_TIME
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ProofOfStakeTime: public Proof {
public:
    void run(Block* block, std::string key) const override;
    bool accept(Block* block, Message* message) const override;
};



#endif //BLOCK_CHAIN_PROOFOFSTAKETIME_H
