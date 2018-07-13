//
// Created by default on 19/4/2561.
//

#include "BlockAskMessage.h"

BlockAskMessage::BlockAskMessage(std::string b, std::string f): Message(Message::ASK_BLOCK), peer(std::move(b)), fingerprint(std::move(f)) {
}

BlockAskMessage::BlockAskMessage() = default;

BlockAskMessage::~BlockAskMessage() = default;

Element* BlockAskMessage::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("peer", ElementCreator::create(peer))
            ->put("fingerprint", ElementCreator::create(fingerprint))
            ->put("type", ElementCreator::create(type));
}

void BlockAskMessage::fromElement(ElementObject* e, const Serializer*, const char*) {
    e->getItem("peer", &peer);
    e->getItem("fingerprint", &fingerprint);
    e->getItem("type", &type);
}