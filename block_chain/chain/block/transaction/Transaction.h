//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_TRANSACTION_H
#define BLOCK_CHAIN_TRANSACTION_H
#include "../../../kernel/components/Component.h"
#include "../../../algorithm/hash/Hash_MD5.h"
#include "../../state/Row.h"

class Serializer;

/**
 *  @class Transaction "block_chain/chain/block/transaction/Transaction.h"
 *  A pure abstract Transaction class. It is the most important
 *  class to be implemented. It is used to represent the
 *  transaction in a block chain.
 *
 *  @author Mathieu Lochet
 *  @version 3
 */
class Transaction: public Component {
public:

    /**
     *  Check if two transactions are the same
     *
     *  @param s Transaction to compare to
     *  @return true if the transactions are the same, false otherwise
     */
    virtual bool operator==(Transaction* s) const = 0;

    /**
     *  Generates the hash for the transaction
     *  @see Hash
     *
     *  @param serializer The serializer
     *  @param encoding The encoding that has been used to create the Element representation of the object
     *  @return the Hash of the Transaction
     */
    std::string __hash__(const Serializer* serializer, const char* encoding) const;

    /**
     *  Apply the transaction to a row
     *  @see Row
     *
     *  @param row The row to update
     *  @return The list of the peers that have to be updated by the reverse transaction
     */
    virtual std::vector<std::string> apply(Row* row) = 0;

    /**
     *  Apply the reverse transaction than apply
     *  @see Row
     *
     *  @param row The row to update
     */
    virtual void apply_reverse(Row* row) = 0;

    /**
     *  Creates a new row
     *  @see Row
     *
     *  @return A newly created Row
     */
    virtual Row* createRow() const = 0;

    /**
     *  Check if the transaction is valid compared to the current state of the row
     *  @see Row
     *
     *  @return true if the transaction is validm false otherwise
     */
    virtual bool validate(Row *row) const = 0;

    /**
     *  Get the type of the transaction
     *
     * @return The type of the transaction
     */
    virtual int get_type() const = 0;

    /**
     *  Get the description of the transaction
     *
     * @return The description of the transaction
     */
    virtual std::string description() const = 0;

    /**
     *  Ask the user's input to fill the transaction
     */
    virtual void fill_data() = 0;

    /**
     *  Creates an empty transaction from the same class
     *
     *  @return the newly created Transaction
     */
    virtual Transaction* clone() = 0;
};


#endif //BLOCK_CHAIN_TRANSACTION_H
