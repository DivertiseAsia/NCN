//
// Created by default on 9/4/2561.
//

#include "Metadata.h"

Element* Metadata::toElement() {
    ElementObject* e = ElementCreator::creator.object();
    return e;
}

void Metadata::fromElement(ElementObject* e) {
}
