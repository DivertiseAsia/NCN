//
// Created by default on 19/4/2561.
//

#include "AskPeersMessage.h"

AskPeersMessage::AskPeersMessage(std::string p): SignMessage(std::move(p), Message::ASK_PEERS){

}

AskPeersMessage::AskPeersMessage() = default;