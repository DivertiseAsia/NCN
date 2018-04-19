//
// Created by default on 19/4/2561.
//

#include "PeersAskParser.h"
#include "../../Node.h"
#include "../messages/Message.h"
#include "../messages/AnswerPeersMessage.h"
#include "../messages/AskPeersMessage.h"

void PeersAskParser::operator()(Message* m, Node* node) const {
    auto* message = dynamic_cast<SignMessage*>(m);
    unsigned long index = message->peer.find(':');
    std::string ip = message->peer.substr(0, index);
    int port = atoi(message->peer.substr(index+1).c_str());
    if(node->debug)
        std::cout << "\033[1;34m[INFO] Peers asked by " << ip << ":" << port<<"\033[0m\n";
    Peer peer(node->serializer, ip, port);
    std::string peers_to_send(node->self.to_string());
    for (auto &p : node->peers)
        peers_to_send += "\n" + p.to_string();
    AnswerPeersMessage mess(peers_to_send);
    char* text = node->serializer->serialize(&mess, node->encoding.c_str());
    peer.send(Encoding::toHexa(std::string(text)).c_str());
    free(text);
}

int PeersAskParser::get_type() const {
    return Message::ASK_PEERS;
};