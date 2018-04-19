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

class Proof {
public:
    static const int WORK;
    static const int STAKE;
    static const int HOLD;
    static const int IMPORTANCE;
    static const int MINIMUM_AGED_STAKE;
    static const int STAKE_TIME;
    static const int USE;
    static void add_proof(int id, std::function<Proof*()>);
    static Proof* generate(int type);
    virtual void run(Block* block, std::string key) = 0;
    virtual bool accept(Block* block, Message*) = 0;
private:
    static std::map<int, std::function<Proof*()>> items;
};


#endif //BLOCK_CHAIN_PROOF_H
