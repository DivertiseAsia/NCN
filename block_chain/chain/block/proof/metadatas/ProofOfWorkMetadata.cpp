//
// Created by default on 17/4/2561.
//

#include "ProofOfWorkMetadata.h"
#include "../../../../algorithm/Hash.h"
#include <iostream>

ProofOfWorkMetadata::ProofOfWorkMetadata(long long int i, long long int j, std::string s): first(i), second(j), winner(s){

}
ProofOfWorkMetadata::ProofOfWorkMetadata() = default;

Element* ProofOfWorkMetadata::toElement() const{
    ElementObject* e = ElementCreator::object();
    return e->put("first", ElementCreator::create(first))
            ->put("second", ElementCreator::create(second))
            ->put("winner", ElementCreator::create(winner))
            ->put("type", ElementCreator::create(0));
}
void ProofOfWorkMetadata::fromElement(ElementObject* e,  const Serializer*, const char*){
    e->getItem("first", &first);
    e->getItem("winner", &winner);
    e->getItem("second", &second);
}

Hash* ProofOfWorkMetadata::hash() {
    return new Hash(winner);
}

void ProofOfWorkMetadata::update_database(Database *pDatabase){
    Row* r = pDatabase->reward(winner);
    if(r)
        r->reward();
}