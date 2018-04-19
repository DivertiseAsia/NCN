//
// Created by default on 19/4/2561.
//

#include "SignInParser.h"
#include "../../Node.h"
#include "../messages/Message.h"
#include "../messages/SignMessage.h"

void SignInParser::operator()(Message* m, Node* node) const {
    auto message = dynamic_cast<SignMessage*>(m);
    unsigned long index = message->peer.find(':');
    std::string ip = message->peer.substr(0, index);
    int port = atoi(message->peer.substr(index+1).c_str());
    if(node->debug)
        std::cout << "\033[1;34m[IN] " << ip << ":" << port << " is signing in in " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
    Peer peer(ip, port);
    node->peers.emplace_back(peer);
}

int SignInParser::get_type() const {
    return Message::SIGN_IN;
};