#include "Message.h"

#include <iostream>

std::string toHexa(std::string str){
    static std::string hexadecimal = "0123456789ABCDEFG";
    std::string hexa;
    for(int i = 0; i < str.size(); i++){
        hexa.append(1, hexadecimal[(str[i]&0xF0) >> 4]).append(1, hexadecimal[str[i]&0x0F]);
    }
    return hexa;
}
Message::Message(std::string p, std::string c, std::string k): plain_text(p), cipher(toHexa(c)), public_key(k), size(cipher.size())
{
}

bool Message::compareResults(std::string c){
    std::string newCipher = toHexa(c);
    std::cout << "Before: " << cipher << std::endl;
    std::cout << "After: " << newCipher << std::endl;
    return cipher == newCipher;
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
                          ->put(e, "plain_text", ElementCreator::creator.create(plain_text));
    return e;
}

void Message::fromElement(ElementObject* e) {
    e->getItem("plain_text", &plain_text);
    e->getItem("cipher", &cipher);
    e->getItem("public_key", &public_key);
    e->getItem("size", &size);
}
