#include "Message.h"

#include <iostream>

const int Message::ASK_PEERS = 0;
const int Message::ANSWER_PEERS = 1;
const int Message::SIGN_IN = 2;
const int Message::SIGN_OUT = 3;
const int Message::TRANSACTION = 4;
const int Message::BLOCK = 5;

Message::Message(std::string p, std::string c, std::string k, int t): plain_text(p), cipher(Encoding::toHexa(c)), public_key(k), size(cipher.size()), type(t)
{
}

bool Message::compareResults(std::string deciphered){
    std::cout << "Plain: " << plain_text << std::endl;
    std::cout << "Decip: " << deciphered << std::endl;
    return plain_text == deciphered;
}

std::string Message::getCipher(){
    static std::string hexadecimal = "0123456789ABCDEFG";
    std::string str;
    for(int i = 0; i < cipher.size(); i += 2)
        str.append(1, (hexadecimal.find(cipher[i]) << 4) + (hexadecimal.find(cipher[i+1])));
    return str;
}


Message::Message()
{
}

Message::~Message()
{
}
Element* Message::toElement() {
    ElementObject* e = ElementCreator::creator.object();
    ElementCreator::creator.put(e, "public_key", ElementCreator::creator.create(public_key))
                          ->put(e, "cipher", ElementCreator::creator.create(cipher))
                          ->put(e, "size", ElementCreator::creator.create(size))
                          ->put(e, "plain_text", ElementCreator::creator.create(plain_text))
                          ->put(e, "type", ElementCreator::creator.create(type));
    return e;
}

void Message::fromElement(ElementObject* e) {
    e->getItem("plain_text", &plain_text);
    e->getItem("cipher", &cipher);
    e->getItem("public_key", &public_key);
    e->getItem("size", &size);
    e->getItem("type", &type);
}
std::string Message::to_string() const {

}