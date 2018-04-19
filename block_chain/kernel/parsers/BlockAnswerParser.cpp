//
// Created by default on 19/4/2561.
//

#include "BlockAnswerParser.h"
#include "../../Node.h"
#include "../messages/Message.h"
#include "../messages/BlockAnswerMessage.h"

void BlockAnswerParser::operator()(Message* m, Node* node) const {
    auto message = dynamic_cast<BlockAnswerMessage*>(m);
    if(node->debug)
        std::cout << "\033[1;34m[INFO] Block Received by " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
    Block *b(node->serializer->unserializeBlock(message->block, node->encoding.c_str()));
    if (node->load(b)) {
        for (auto &a : node->waiting)
            node->block_chain.add(a);
        node->waiting.clear();
    }
}

int BlockAnswerParser::get_type() const {
    return Message::ANSWER_BLOCK;
};