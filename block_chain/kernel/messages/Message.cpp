#include "Message.h"
#include "TransactionMessage.h"
#include "BlockAskMessage.h"
#include "SignInMessage.h"
#include "SignOutMessage.h"
#include "BlockAnswerMessage.h"
#include "AskPeersMessage.h"
#include "AnswerPeersMessage.h"
#include "BlockMessage.h"

#include <iostream>
#include <utility>

const int Message::ASK_PEERS = 0;
const int Message::ANSWER_PEERS = 1;
const int Message::SIGN_IN = 2;
const int Message::SIGN_OUT = 3;
const int Message::TRANSACTION = 4;
const int Message::BLOCK = 5;
const int Message::ASK_BLOCK = 6;
const int Message::ANSWER_BLOCK = 7;
/*
Message::Message(std::string p, std::string c, std::string k, MerkleTree* tr, int t): plain_text(std::move(std::move(p))), cipher(Encoding::toHexa(
        std::move(c))), public_key(
        std::move(
                std::move(k))), type(t), tree(tr)
{
}*/

Message::Message(const int i): type(i){

}

/*
bool Message::compareResults(std::string deciphered){
    return plain_text == deciphered;
}

std::string Message::getCipher(){
    return Encoding::fromHexa(cipher);
}
*/

Message::Message() = default;

Message::~Message() = default;

Message* Message::generate(int id){
    static std::map<int, std::function<Message*()>> message;
    if(message.empty()){
        message[BLOCK] =  []() -> Message*{return new BlockMessage;};
        message[ASK_PEERS] =  []() -> Message*{return new AskPeersMessage;};
        message[ANSWER_PEERS] =  []() -> Message*{return new AnswerPeersMessage;};
        message[SIGN_IN] =  []() -> Message*{return new SignInMessage;};
        message[SIGN_OUT] =  []() -> Message*{return new SignOutMessage;};
        message[ASK_BLOCK] =  []() -> Message*{return new BlockAskMessage;};
        message[ANSWER_BLOCK] =  []() -> Message*{return new BlockAnswerMessage;};
        message[TRANSACTION] =  []() -> Message*{return new TransactionMessage;};
    }
    return message.find(id)->second();
}

const int Message::get_type() const{
    return type;
}
