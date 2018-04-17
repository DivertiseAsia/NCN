//
// Created by default on 17/4/2561.
//

#include "ProofOfWorkMetadata.h"
#include <iostream>

ProofOfWorkMetadata::ProofOfWorkMetadata(double i, double j): first(i), second(j){

}
ProofOfWorkMetadata::ProofOfWorkMetadata() = default;

Element* ProofOfWorkMetadata::toElement() const{
    ElementObject* e = ElementCreator::object();
    return e->put("first", ElementCreator::create(first))
            ->put("second", ElementCreator::create(second))
            ->put("type", ElementCreator::create(0));
}
void ProofOfWorkMetadata::fromElement(ElementObject* e,  const Serializer*, const char*){
    e->getItem("first", &first);
    e->getItem("second", &second);
}