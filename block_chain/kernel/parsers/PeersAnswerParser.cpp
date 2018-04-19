//
// Created by default on 19/4/2561.
//

#include "PeersAnswerParser.h"
#include "../../Node.h"
#include "../messages/Message.h"
#include "../messages/SignInMessage.h"

void PeersAnswerParser::operator()(Message* m, Node* node) const {
    auto* message = dynamic_cast<SignMessage*>(m);
    if(node->debug)
        std::cout << "\033[1;34m[INFO] Peers received by " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
    SignInMessage mess(node->self.to_string());
    char* text = node->serializer->serialize(&mess, node->encoding.c_str());
    std::istringstream list(message->peer);
    std::string line;
    while (std::getline (list, line)) {
        unsigned long index = line.find(':');
        std::string ip = line.substr(0, index);
        int port = atoi(line.substr(index+1).c_str());
        if(ip != node->self._ip || port != node->self._port) {
            Peer peer(ip, port);
            node->peers.emplace_back(peer);
            peer.send(Encoding::toHexa(std::string(text)).c_str());
        }
    }
    free(text);
    node->block_chain.read_blocks();
}

int PeersAnswerParser::get_type() const {
    return Message::ANSWER_PEERS;
};