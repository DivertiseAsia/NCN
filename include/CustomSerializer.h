#ifndef CUSTOMSERIALIZER_H
#define CUSTOMSERIALIZER_H

#include "../block_chain/Serializer.h"
#include "../transactions/MessagesTransaction.h"
#include "../transactions/StatusTransaction.h"

class CustomSerializer: public Serializer
{
    public:
        virtual Transaction* unserializeTransaction(std::string transaction, const char* key) const;
};

#endif // CUSTOMSERIALIZER_H
