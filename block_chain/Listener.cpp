//
// Created by default on 3/4/2561.
//

#include "Listener.h"
#include <iostream>

Listener::Listener(Node* c, int p, Serializer* s): client(c), port(p), serializer(s) {

}

Listener::~Listener(){
    delete thread;
}

void Listener::start(bool(* callback)(Socket*, int, Serializer*, Node*), void (*func)(bool(*)(Socket*, int, Serializer*, Node*), Node*, int, Serializer*)) {
    thread = new std::thread(func, callback, client, port, serializer);
}
