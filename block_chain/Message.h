#ifndef MESSAGE_H
#define MESSAGE_H

#include"chain/block/Component.h"
#include <sstream>
#include <fstream>
#include "utils/Encoding.h"

class Message: public Component
{
    friend class Node;
    public:
        Message();
        Message(std::string p, std::string c, std::string k);
        ~Message();
        Element* toElement();
        bool compareResults(std::string cipher);
        std::string getCipher();
    protected:
        void fromElement(ElementObject*);

    private:
        int size;
        std::string plain_text;
        std::string cipher;
        std::string public_key;
};

#endif // MESSAGE_H
