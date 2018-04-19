//
// Created by default on 19/4/2561.
//

#include "BlockAskParser.h"
#include "../../Node.h"
#include "../messages/Message.h"
#include "../messages/BlockAskMessage.h"
#include "../messages/BlockAnswerMessage.h"

void BlockAskParser::operator()(Message* m, Node* node) const {
    auto message = dynamic_cast<BlockAskMessage*>(m);
    unsigned long index = message->block.find(':');
    std::string ip = message->block.substr(0, index);
    int port = atoi(message->block.substr(index+1).c_str());
    if(node->debug)
        std::cout << "\033[1;34m[INFO] Block "<< Encoding::fromHexa(message->fingerprint) << " asked by " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
    std::string hash = Encoding::fromHexa(message->fingerprint);
    Block* b = node->block_chain.get(hash);
    std::string serialized_block(node->serializer->serialize(b, node->encoding.c_str()));
    BlockAnswerMessage answer(serialized_block);
    char* text = node->serializer->serialize(&answer, node->encoding.c_str());
    Peer peer(ip, port);
    peer.send(Encoding::toHexa(std::string(text)).c_str());
    free(text);
}

int BlockAskParser::get_type() const {
    return Message::ASK_BLOCK;
};