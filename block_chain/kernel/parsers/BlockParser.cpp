//
// Created by default on 19/4/2561.
//

#include "BlockParser.h"
#include "../../Node.h"
#include "../messages/Message.h"

void BlockParser::operator()(Message* m, Node* node) const {
    auto message = dynamic_cast<BlockMessage*>(m);
    if(node->debug)
        std::cout << "\033[1;32m[INFO] Block parsed by " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
    RSA_Cryptography crypto(message->get_key());
    Block* block(node->serializer->unserializeBlock(message->block, node->encoding.c_str()));

    if(node->debug)
        std::cout << "\033[1;32m[INFO] Block computed by " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
    if(node->load(block) && block->checkFingerPrint(node->serializer, node->encoding.c_str()))
    {
        if(node->debug)
            std::cout << "\033[1;32m[INFO] Block accepted\033[0m\n";
        if(node->proof->accept(block, message)) {
            int i = 0;
            for (auto &t : block->transactions) {
                std::string cipher(Encoding::fromHexa(t.first));
                RSA_Cryptography crypto(Encoding::fromHexa(t.second));
                Transaction *transaction = node->serializer->unserializeTransaction(crypto.decrypt(cipher, cipher.size()), node->encoding.c_str());
                bool valid = *message->tree->get_hash(i) == *transaction->__hash__(node->serializer, node->encoding.c_str());
                if (!valid)
                    return;
                i++;
            }
            if(node->debug)
                std::cout << "\033[1;32m[INFO] New Block\033[0m\n";
            node->queue--;
            if(node->queue < 0)
                node->queue = 0;
            node->block_chain.add(block);
        }
        else if(node->debug)
            std::cout << "\033[1;32m[INFO] Invalid proof\033[0m\n";
    }
    else if(node->debug)
        std::cout << "\033[1;32m[INFO] Invalid validator\033[0m\n";
}

int BlockParser::get_type() const {
    return Message::BLOCK;
};