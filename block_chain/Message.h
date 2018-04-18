#ifndef MESSAGE_H
#define MESSAGE_H

#include"chain/block/Component.h"
#include <sstream>
#include <fstream>
#include "utils/Encoding.h"
#include "chain/block/transaction/MerkleTree.h"

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
        static const int ASK_BLOCK;
        static const int ANSWER_BLOCK;
        Message();
        Message(std::string p, std::string c, std::string k, MerkleTree*, int);
        ~Message() override;
        Element* toElement() const override;
        bool compareResults(std::string cipher);
        std::string getCipher();
        int type;
        std::string to_string() const;
        std::string public_key;
    protected:
        void fromElement(ElementObject*, const Serializer* serializer, const char* encoding) override;

    private:
        std::string plain_text;
        std::string cipher;
        MerkleTree* tree;


};

#endif // MESSAGE_H
