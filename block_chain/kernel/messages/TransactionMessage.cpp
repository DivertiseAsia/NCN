//
// Created by default on 19/4/2561.
//

#include "TransactionMessage.h"

TransactionMessage::TransactionMessage(std::string p, std::string c, std::string k, MerkleTree* tr): Message(Message::TRANSACTION), plain_text(std::move(p)), cipher(Encoding::toHexa(
        std::move(c))), public_key(std::move(k)), tree(tr)
{
}

bool TransactionMessage::compareResults(std::string deciphered){
    return plain_text == deciphered;
}

std::string TransactionMessage::getCipher(){
    return Encoding::fromHexa(cipher);
}


TransactionMessage::TransactionMessage() = default;

TransactionMessage::~TransactionMessage() = default;

Element* TransactionMessage::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("public_key", ElementCreator::create(public_key))
            ->put("cipher", ElementCreator::create(cipher))
            ->put("plain_text", ElementCreator::create(plain_text))
            ->put("type", ElementCreator::create(type))
            ->put("tree", tree != nullptr ? tree->toElement() : ElementCreator::create(type));
}

void TransactionMessage::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
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
std::string TransactionMessage::to_string() const {

}