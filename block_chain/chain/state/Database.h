//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_DATABASE_H
#define BLOCK_CHAIN_DATABASE_H

#include <map>
#include <string>
#include "Row.h"
#include "../block/transaction/Transaction.h"
#include "../block/transaction/Reward.h"

/**
 *  A database object is filled by a list of rows
 *  It needs to be easily updated and duplicated
 *  @see Row
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class Database {
    friend class Chain;
public:

    /**
     *  A constructor that accepts a reward transaction
     *  @see Reward
     *
     *  @param r The reward transaction that will be used in the reward method
     */
    explicit Database(Reward* r);

    /**
     *  A constructor to clone a database with different pointers
     *
     *  @param d The database to be duplicated
     */
    Database(Database const& d);

    /**
     *  Get the row corresponding to the user's key
     *
     *  @param key The users key
     *  @return The user's row representing its datas
     */
    Row *get(std::string key);

    /**
     *  Get the row corresponding to the user's key.
     *  If the row is not found, it will create a new one
     *
     *  @param winner The users key
     *  @return The user's row representing its datas
     */
    Row* reward(std::string winner);

private:

    /**
     *  The list of the rows in the database
     */
    std::map<std::string, Row*> rows;

    /**
     *  The reward transaction to be used
     */
    Reward* reward_transaction;
};


#endif //BLOCK_CHAIN_DATABASE_H