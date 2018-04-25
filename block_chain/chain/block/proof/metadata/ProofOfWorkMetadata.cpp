//
// Created by default on 17/4/2561.
//

#include "ProofOfWorkMetadata.h"
#include "../../../../algorithm/hash/Hash_MD5.h"
#include <iostream>

const int ProofOfWorkMetadata::TYPE = 0;
ProofOfWorkMetadata::ProofOfWorkMetadata(long long int i, long long int j, std::string s): Metadata(s), first(i), second(j){

}
ProofOfWorkMetadata::ProofOfWorkMetadata() = default;

Element* ProofOfWorkMetadata::toElement() const{
    Element* e = Metadata::toElement();
    auto o = dynamic_cast<ElementObject*>(e);
    return o->put("first", ElementCreator::create(first))
            ->put("second", ElementCreator::create(second))
            ->put("type", ElementCreator::create(ProofOfWorkMetadata::TYPE));
}
void ProofOfWorkMetadata::fromElement(ElementObject* e,  const Serializer* serializer, const char* encoding){
    Metadata::fromElement(e, serializer, encoding);
    e->getItem("first", &first);
    e->getItem("creator", &creator);
    e->getItem("second", &second);
}

std::string ProofOfWorkMetadata::hash() {
    return Hash::get_hash()->generate_hash(creator);
}

void ProofOfWorkMetadata::update_database(Database *pDatabase){
    Row* r = pDatabase->reward(creator);
    if(r)
        r->reward();
}