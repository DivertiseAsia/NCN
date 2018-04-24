//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_REWARDTRANSACTION_H
#define BLOCK_CHAIN_REWARDTRANSACTION_H


#include "../block_chain/chain/block/transaction/Reward.h"

/**
 *  @class RewardTransaction "reward/RewardTransaction.h"
 *  A custom Reward for testing
 *  @see Serializer
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class RewardTransaction: public Reward
{
public:
    explicit RewardTransaction();
    Transaction* clone() override;
    Row* createRow() const override;
};


#endif //BLOCK_CHAIN_REWARDTRANSACTION_H
