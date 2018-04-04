//
// Created by default on 4/4/2561.
//

#include "Serializer.h"

char* Serializer::serialize(Transaction* transaction) const{
    return transaction->serialize();
}
char* Serializer::serialize(Block* block) const {
    return "The game";
}
char* Serializer::unserialize(Transaction* transaction) const {
    return "The game";
}
char* Serializer::unserialize(Block* block) const {
    return "The game";
}