//
// Created by default on 25/4/2561.
//

#ifndef BLOCK_CHAIN_FRAMEWORK_H
#define BLOCK_CHAIN_FRAMEWORK_H


#include <vector>
#include "chain/block/transaction/Transaction.h"
#include "TransactionManager.h"

/**
 *  @class Framework "block_chain/Framework.h"
 *  An helper class for generating both TransactionManager
 *  and Serializer without having to handle any lambda expression
 *  @see Transaction
 *  @see TransactionManager
 *  @see Serializer
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class Framework {
public:

    /**
     *  Basic constructor for initialization
     */
    Framework();

    /**
     *  Free the resources
     */
    ~Framework();

    /**
     *  Add a new transaction to the object
     *  @see Transaction
     *
     *  @param transaction A new Transaction to add in the object
     */
    void add_transaction(Transaction* transaction);

    /**
     *  Generates the TransactionManager with all of
     *  the given Transaction
     *  @see TransactionManager
     *
     *  @return The TransactionManager for running the loop
     */
    const TransactionManager generate_manager();

    /**
     *  Generates the Serializer with all of
     *  the given Transaction
     *  @see Serializer
     *
     *  @return The Serializer for all of the serialization process
     */
    Serializer* generate_serializer();
private:

    /**
     *  The TransactionManager to fill with Transaction
     */
    TransactionManager manager;

    /**
     *  The Serializer object to fill with lambda expression for Transaction generation
     */
    Serializer* serializer;

    /**
     *  The list of given Transaction
     */
    std::vector<Transaction*> transactions;
};


#endif //BLOCK_CHAIN_FRAMEWORK_H
