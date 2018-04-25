//
// Created by default on 19/4/2561.
//

#include "BlockAnswerParser.h"
#include "BlockParser.h"
#include "../../Node.h"
#include "../messages/Message.h"
#include "../messages/BlockAnswerMessage.h"

void BlockAnswerParser::operator()(Message* m, Node* node) const {
    auto message = dynamic_cast<BlockAnswerMessage*>(m);
    if(node->debug)
        std::cout << "\033[1;34m[INFO] Block Received by " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
    Block *b(node->serializer->unserializeBlock(message->block, node->encoding.c_str()));
    if (node->load(b)) {
        MessageParser* parser = node->parsers.find(Message::BLOCK)->second;
        for (auto &a : node->waiting){

            //node->block_chain.add(a);

            std::string serialized_block(node->serializer->serialize(a, node->encoding.c_str()));
            MerkleTree tree(a, node->serializer, node->encoding.c_str(), node->crypto_id);
            BlockMessage answer(serialized_block, message->key, &tree);
            (*parser)(message, node);
        }
        delete parser;
        node->waiting.clear();
    }
}

int BlockAnswerParser::get_type() const {
    return Message::ANSWER_BLOCK;
};