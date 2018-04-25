//
// Created by default on 19/4/2561.
//

#include "TransactionParser.h"
#include "../../Node.h"
#include "../messages/Message.h"
#include "../messages/TransactionMessage.h"

void TransactionParser::operator()(Message* m, Node* node) const {
    auto message = dynamic_cast<TransactionMessage*>(m);
    if(node->debug)
        std::cout << "\033[1;32m[INFO] Transaction parsed by " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
    RSA_Cryptography crypto(message->public_key);
    std::string str(message->getCipher());
    Transaction* deciphered(node->serializer->unserializeTransaction(crypto.decrypt(str, (int)str.size()), node->encoding.c_str()));
    Transaction* transaction(node->serializer->unserializeTransaction(message->plain_text, node->encoding.c_str()));
    if(*deciphered == transaction){
        if(node->debug)
            std::cout << "\033[1;32m[INFO] Transaction computed by " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
        bool valid = (message->tree->value == transaction->__hash__(node->serializer, node->encoding.c_str()) && node->block_chain.check_transaction(transaction, message->public_key));
        if(valid) {
            Block *block = node->block_chain.add(message->cipher, Encoding::toHexa(message->public_key));
            if(block != nullptr){
                node->queue++;
                node->proof->run(block, Encoding::toHexa(node->rsa.getPublicKey()));
                block->update_fingerprint(node->serializer, node->encoding.c_str());
                std::vector<Transaction*> transactions;
                for(auto& t : block->transactions){
                    std::string cipher(Encoding::fromHexa(t.first));
                    RSA_Cryptography crypto(Encoding::fromHexa(t.second));
                    transactions.emplace_back(node->serializer->unserializeTransaction(crypto.decrypt(cipher, cipher.size()), node->encoding.c_str()));
                }
                std::string serialized_block(node->serializer->serialize(block, node->encoding.c_str()));
                MerkleTree tree(transactions, node->serializer, node->encoding.c_str());
                BlockMessage answer(serialized_block, node->rsa.getPublicKey(), &tree);
                char* m = node->serializer->serialize(&answer, node->encoding.c_str());
                if(node->queue > 0) {
                    for (auto &peer : node->peers)
                        peer.send(Encoding::toHexa(std::string(m)).c_str());
                    node->self.send(Encoding::toHexa(std::string(m)).c_str());
                }
                free(m);
            }
        }
    }
    else
        delete transaction;
    delete deciphered;
}

int TransactionParser::get_type() const {
    return Message::TRANSACTION;
};