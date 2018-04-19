//
// Created by default on 19/4/2561.
//

#include "AnswerPeersMessage.h"

AnswerPeersMessage::AnswerPeersMessage(std::string p): SignMessage(p, Message::ANSWER_PEERS){

}

AnswerPeersMessage::AnswerPeersMessage() = default;