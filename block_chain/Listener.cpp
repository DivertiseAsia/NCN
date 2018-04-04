//
// Created by default on 3/4/2561.
//

#include "Listener.h"
#include <iostream>

Listener::Listener(Client* c, int p): client(c), port(p) {

}

Listener::~Listener(){
    delete thread;
}

void Listener::start(void (*func)(Client*, int)) {
    thread = new std::thread(func, client, port);
}
