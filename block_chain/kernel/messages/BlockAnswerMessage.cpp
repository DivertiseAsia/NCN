//
// Created by default on 19/4/2561.
//

#include "BlockAnswerMessage.h"

BlockAnswerMessage::BlockAnswerMessage(std::string p, std::string k): Message(Message::ANSWER_BLOCK), block(std::move(p)), key(std::move(k)) {
}

BlockAnswerMessage::BlockAnswerMessage() = default;

BlockAnswerMessage::~BlockAnswerMessage() = default;

Element* BlockAnswerMessage::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("block", ElementCreator::create(block))
            ->put("key", ElementCreator::create(key))
            ->put("type", ElementCreator::create(type));
}

void BlockAnswerMessage::fromElement(ElementObject* e, const Serializer*, const char*) {
    e->getItem("block", &block);
    e->getItem("type", &type);
    e->getItem("key", &key);
}