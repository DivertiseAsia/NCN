//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_REWARD_H
#define BLOCK_CHAIN_REWARD_H


#include "Transaction.h"

/**
 *  @class Reward "block_chain/chain/block/transaction/Reward.h"
 *  An abstract reward class. It is a special case of Transaction
 *  With only a few method to override. It is needed to update
 *  the database when there is a Block validation
 *  @see Transaction
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class Reward: public Transaction {
public:
    explicit Reward();
    //bool operator()() const final;
    Element* toElement() const final;
    bool operator==(Transaction* t) const final {
        auto * s = dynamic_cast<Reward*>(t);
        return s != nullptr;
    }
    void apply_reverse(Row* row) final;
    bool validate(Row *row) const final;
    int get_type() const final;
    std::string description() const final;
    void fill_data() final;
    std::vector<std::string> apply(Row* row) override;
protected:
    void fromElement(ElementObject*, const Serializer*, const char* encoding) final;
};

#endif //BLOCK_CHAIN_REWARD_H
