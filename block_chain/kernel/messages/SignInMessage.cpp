//
// Created by default on 19/4/2561.
//

#include "SignInMessage.h"

SignInMessage::SignInMessage(std::string p): SignMessage(std::move(p), Message::SIGN_IN){

}

SignInMessage::SignInMessage() = default;