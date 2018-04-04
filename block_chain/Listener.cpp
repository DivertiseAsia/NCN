//
// Created by default on 3/4/2561.
//

#include "Listener.h"
#include <iostream>

Listener::Listener(Node* c, int p): client(c), port(p) {

}

Listener::~Listener(){
    delete thread;
}

void Listener::start(void (*func)(Node*, int)) {
    thread = new std::thread(func, client, port);
}
