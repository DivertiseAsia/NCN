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
        static const int TRANSACTION;
        static const int BLOCK;
        static const int ASK_PEERS;
        static const int ANSWER_PEERS;
        static const int SIGN_IN;
        static const int SIGN_OUT;
        Message();
        Message(std::string p, std::string c, std::string k, int);
        ~Message();
        Element* toElement();
        bool compareResults(std::string cipher);
        std::string getCipher();
        int type;
        std::string to_string() const;
    protected:
        void fromElement(ElementObject*);

    private:
        int size;
        std::string plain_text;
        std::string cipher;
        std::string public_key;
};

#endif // MESSAGE_H
