//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFWORK_H
#define BLOCK_CHAIN_PROOFOFWORK_H


#include "Proof.h"

/**
 *  A basic proof of work
 *  @see Proof
 *  @see Proof::WORK
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ProofOfWork: public Proof {
public:
    void run(Block* block, std::string key) const override;
    bool accept(Block* block, Message*) const override;
};


#endif //BLOCK_CHAIN_PROOFOFWORK_H
