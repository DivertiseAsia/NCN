//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFIMPORTANCE_H
#define BLOCK_CHAIN_PROOFOFIMPORTANCE_H


#include "Proof.h"

/**
 *  A basic proof of importance
 *  @see Proof
 *  @see Proof::IMPORTANCE
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ProofOfImportance: public Proof {
public:
    void run(Block* block, std::string key) override;
    bool accept(Block* block, Message* message) override;
};



#endif //BLOCK_CHAIN_PROOFOFIMPORTANCE_H
