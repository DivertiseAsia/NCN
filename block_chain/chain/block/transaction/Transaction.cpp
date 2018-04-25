//
// Created by default on 3/4/2561.
//

#include "Transaction.h"
#include "../../../utils/serialization/Serializer.h"


std::string Transaction::__hash__(const Serializer* serializer, const char* encoding) const{
    return Hash::get_hash()->generate_hash(this, serializer, encoding);
}
