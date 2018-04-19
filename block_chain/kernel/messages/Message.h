#ifndef MESSAGE_H
#define MESSAGE_H

#include"../components/Component.h"
#include <sstream>
#include <fstream>
#include "../../utils/Encoding.h"
#include "../../algorithm/MerkleTree.h"
#include <functional>

class Message: public Component
{
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
        explicit Message(int i);
        ~Message() override;
        static Message* generate(int id);
        const int get_type() const;
protected:
        int type;
};

#endif // MESSAGE_H
