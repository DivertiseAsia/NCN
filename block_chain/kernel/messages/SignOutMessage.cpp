//
// Created by default on 19/4/2561.
//

#include "SignOutMessage.h"

SignOutMessage::SignOutMessage(std::string p): SignMessage(std::move(p), Message::SIGN_OUT){

}

SignOutMessage::SignOutMessage() = default;