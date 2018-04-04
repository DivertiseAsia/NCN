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

void Listener::start(bool(* callback)(Socket*, int), void (*func)(bool(*)(Socket*, int), Node*, int)) {
    thread = new std::thread(func, callback, client, port);
}