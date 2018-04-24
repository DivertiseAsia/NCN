//
// Created by default on 9/4/2561.
//

#include "Metadata.h"

Element* Metadata::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("creator", ElementCreator::create(creator));
}

void Metadata::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    e->getItem("creator", &creator);
}

Metadata::Metadata() = default;

Metadata::~Metadata() = default;

std::string Metadata::get_creator() {
    return creator;
}

Metadata::Metadata(std::string c): creator(std::move(c)) {

}
