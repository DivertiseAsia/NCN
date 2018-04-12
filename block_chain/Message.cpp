#include "Message.h"

#include <iostream>
#include <utility>

const int Message::ASK_PEERS = 0;
const int Message::ANSWER_PEERS = 1;
const int Message::SIGN_IN = 2;
const int Message::SIGN_OUT = 3;
const int Message::TRANSACTION = 4;
const int Message::BLOCK = 5;

Message::Message(std::string p, std::string c, std::string k, MerkleTree* tr, int t): plain_text(std::move(std::move(p))), cipher(Encoding::toHexa(
        std::move(c))), public_key(
        std::move(
                std::move(k))), type(t), tree(tr)
{
}

bool Message::compareResults(std::string deciphered){
    return plain_text == deciphered;
}

std::string Message::getCipher(){
    return Encoding::fromHexa(cipher);
}


Message::Message() = default;

Message::~Message() = default;

Element* Message::toElement() const {
    ElementObject* e = ElementCreator::object();
    e->put("public_key", ElementCreator::create(public_key))
                          ->put("cipher", ElementCreator::create(cipher))
                          ->put("plain_text", ElementCreator::create(plain_text))
                          ->put("type", ElementCreator::create(type))
                          ->put("tree", tree != nullptr ? tree->toElement() : ElementCreator::create(type));
    return e;
}

void Message::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    e->getItem("plain_text", &plain_text);
    e->getItem("cipher", &cipher);
    e->getItem("public_key", &public_key);
    e->getItem("type", &type);
    ElementObject* o = nullptr;
    e->getItem("tree", &o);
    if(o && !o->values.empty()) {
        tree = new MerkleTree();
        tree->fromElement(o, serializer, encoding);
    }
    else
        tree = nullptr;
}
std::string Message::to_string() const {

}
