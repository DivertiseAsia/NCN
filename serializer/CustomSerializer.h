#ifndef CUSTOMSERIALIZER_H
#define CUSTOMSERIALIZER_H

#include "../block_chain/utils/serialization/Serializer.h"
#include "../transactions/MessagesTransaction.h"
#include "../transactions/StatusTransaction.h"

/**
 *  @class CustomSerializer "serializer/CustomSerializer.h"
 *  A custom Serializer for testing
 *  @see Serializer
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class CustomSerializer: public Serializer
{
    public:
    Transaction* unserializeTransaction(std::string transaction, const char* key) const override;
};

#endif // CUSTOMSERIALIZER_H
