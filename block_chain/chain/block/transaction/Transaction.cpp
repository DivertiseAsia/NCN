//
// Created by default on 3/4/2561.
//

#include "Transaction.h"
#include "../../../Serializer.h"


Hash* Transaction::__hash__(const Serializer* serializer, const char* encoding) const{
    return new Hash(this, serializer, encoding);
}
