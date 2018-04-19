//
// Created by default on 19/4/2561.
//

#include "SignOutParser.h"
#include "../../Node.h"
#include "../messages/Message.h"
#include "../messages/SignMessage.h"

void SignOutParser::operator()(Message* m, Node* node) const {
    auto message = dynamic_cast<SignMessage*>(m);
    unsigned long index = message->peer.find(':');
    std::string ip = message->peer.substr(0, index);
    int port = atoi(message->peer.substr(index+1).c_str());
    if(node->debug)
        std::cout << "\033[1;34m[OUT] " << ip << ":" << port << " is signing out from " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
    Peer peer(node->serializer, ip, port);
    auto it = find(node->peers.begin(), node->peers.end(), peer);
    if(it != node->peers.end()) {
        it->close();
        node->peers.erase(it);
    }
}

int SignOutParser::get_type() const {
    return Message::SIGN_OUT;
};