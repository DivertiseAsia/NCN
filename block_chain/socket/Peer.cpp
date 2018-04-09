//
// Created by default on 4/4/2561.
//

#include "Peer.h"

Peer::Peer(Serializer* s, std::string ip, int c, int t, int b): serializer(s), transaction_socket(new Socket(ip, t)), block_socket(new Socket(ip, b)), socket(new Socket(ip, c)){

}

void Peer::sign_out(Peer p) const{

}

void Peer::sendTransaction(char* text){
    if(socket != nullptr)
        transaction_socket->write(text);
}

void Peer::sendBlock(char* text){
    if(socket != nullptr)
        block_socket->write(text);
}
