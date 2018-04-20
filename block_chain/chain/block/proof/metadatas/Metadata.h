//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_METADATA_H
#define BLOCK_CHAIN_METADATA_H


#include "../../../../utils/serialization/Element.h"
#include "../../../../kernel/components/Component.h"
#include "../../../../algorithm/Hash.h"
#include "../../../state/Database.h"

/**
 *  An abstract metadata class representing a block's header.
 *  Needs to be reimplemented with the proper header representation
 *  @see Block
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class Metadata:public Component{
public:

    /**
     *  A virtual default destructor
     */
    virtual ~Metadata();

    /**
     *  Overriding the == operator
     *
     *  @param m A metadata to be compared
     *  @return true if the conditions are satisfied, false otherwise
     */
    virtual bool operator==(Metadata& m) const{
        return false;
    }

    /**
     *  Update the database with the reward transaction
     *  when the block is validated
     *
     *  @param d The database to update
     */
    virtual void update_database(Database *d) = 0;

    /**
     *  Get the hash ofthe user who validated the block
     *
     *  @return The hash ofthe user who validated the block
     */
    virtual Hash* hash() = 0;
};
#endif //BLOCK_CHAIN_METADATA_H
