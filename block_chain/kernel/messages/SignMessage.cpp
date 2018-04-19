//
// Created by default on 19/4/2561.
//

#include "SignMessage.h"

SignMessage::SignMessage(std::string p, int t): Message(t), peer(std::move(p)) {
}

SignMessage::SignMessage() = default;

SignMessage::~SignMessage() = default;

Element* SignMessage::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("peer", ElementCreator::create(peer))
            ->put("type", ElementCreator::create(type));
}

void SignMessage::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    e->getItem("peer", &peer);
    e->getItem("type", &type);
}