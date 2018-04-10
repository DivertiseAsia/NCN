//
// Created by default on 4/4/2561.
//

#include "Peer.h"

Peer::Peer(Serializer* s, std::string ip, int c): serializer(s), socket(new Socket(ip, c)) {
    _ip = ip;
    _port = c;
}

void Peer::sign_out(Peer p) const{

}

int Peer::send(const char* text) const{
    if(socket != nullptr)
        return socket->write(text);
    return 0;
}

std::string Peer::to_string() const {
    return _ip + std::string(":") + std::to_string(_port);
}