//
// Created by default on 3/4/2561.
//

#include "Transaction.h"
#include "../../../Serializer.h"


void Transaction::__hash__(Serializer* serializer, const char* encoding) {
    hash = new Hash(this, serializer, encoding);
}