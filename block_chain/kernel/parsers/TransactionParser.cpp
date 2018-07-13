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
    Cryptography* crypto(Cryptography::generate(node->crypto_id, message->public_key));
    std::string str(message->getCipher());
    Transaction* deciphered(node->serializer->unserializeTransaction(crypto->decrypt(str, str.size()), node->encoding.c_str()));
    Transaction* transaction(node->serializer->unserializeTransaction(message->plain_text, node->encoding.c_str()));
    if(*deciphered == transaction){
        if(node->debug)
            std::cout << "\033[1;32m[INFO] Transaction computed by " << node->self._ip << ":" << node->self._port<<"\033[0m\n";
        bool valid = (message->tree->value == transaction->__hash__(node->serializer, node->encoding.c_str()) && node->block_chain.check_transaction(transaction, message->public_key));
        if(valid) {
            Block *block = node->block_chain.add(message->cipher, Encoding::toHexa(message->public_key));
            if(block != nullptr){
                node->queue++;
                node->proof->run(block, Encoding::toHexa(node->crypto->getPublicKey()));
                block->update_fingerprint(node->serializer, node->encoding.c_str(), node->crypto_id);
                std::vector<Transaction*> transactions;
                for(auto& t : block->transactions){
                    std::string cipher(Encoding::fromHexa(t.first));
                    Cryptography* tmp_crypto(Cryptography::generate(node->crypto_id, Encoding::fromHexa(t.second)));
                    transactions.emplace_back(node->serializer->unserializeTransaction(tmp_crypto->decrypt(cipher, cipher.size()), node->encoding.c_str()));
                    delete tmp_crypto;
                }
                std::string serialized_block(node->serializer->serialize(block, node->encoding.c_str()));
                MerkleTree tree(transactions, node->serializer, node->encoding.c_str());
                BlockMessage answer(serialized_block, node->crypto->getPublicKey(), &tree);
                char* mess = node->serializer->serialize(&answer, node->encoding.c_str());
                if(node->queue > 0) {
                    for (auto &peer : node->peers)
                        peer.send(Encoding::toHexa(std::string(mess)).c_str());
                    node->self.send(Encoding::toHexa(std::string(mess)).c_str());
                }
                free(mess);
            }
        }
    }
    else
        delete transaction;
    delete crypto;
    delete deciphered;
}

int TransactionParser::get_type() const {
    return Message::TRANSACTION;
};