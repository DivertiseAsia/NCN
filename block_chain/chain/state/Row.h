//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_ROW_H
#define BLOCK_CHAIN_ROW_H


#include <string>

/**
 *  @class Row "block_chain/chain/state/Row.h"
 *  An abstract row in the database.
 *  Needs to be reimplemented so the user can
 *  create any representation of data he wants.
 *  @see Database
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class Row {
public:

    /**
     *  A default virtual destructor
     */
    virtual ~Row() = default;

    /**
     *  A method to duplicate the row.
     *  It needs to be reimplemented and
     *  to do an exact copy of itself
     *
     *  @return Return the cloned Row
     */
    virtual Row* clone() const = 0;

    /**
     *  Generate the string representation of a database's row
     *  It needs to be implemented
     *
     *  @return The string representation of the row
     */
    virtual std::string to_string() const = 0;

    /**
     *  Change the row to add the reward
     *  for validating the block
     */
    virtual void reward() = 0;
};


#endif //BLOCK_CHAIN_ROW_H
