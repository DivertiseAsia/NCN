//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTION_MANAGER_H
#define BLOCK_CHAIN_TRANSACTION_MANAGER_H


#include "chain/block/transaction/Transaction.h"

/**
 *  @class TransactionManager "block_chain/TransactionManager.h"
 *  The manager class of all transactions.
 *  It generates transactions based on the ones
 *  it indexed
 *  @see Transaction
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class TransactionManager {
public:

	/**
	 *  Default constructor to initialize the manager
	 */
    TransactionManager();
	
	/**
	 *  The destructor frees all of the indexed transactions
	 */
    ~TransactionManager();
	
	/**
	 *  Add a new transaction to the list of transactions
	 *  @see Transaction
	 * 
	 *  @param t The new transaction to add to the manager's index
	 */
    void put(Transaction* t);

	/**
	 *  Run the manager and generates transactions based on user's input_iterator
	 *  @see Transaction
	 *
	 *  @return The newly created Transaction (-1 if show the database and nullptr otherwise)
	 */
    Transaction* run();
private:

	/**
	 *  The list of all different transactions,
	 *  indexed by their type
	 *  @see Transaction
	 */
    std::map<int, Transaction*> transactions;
};


#endif //BLOCK_CHAIN_TRANSACTION_MANAGER_H
