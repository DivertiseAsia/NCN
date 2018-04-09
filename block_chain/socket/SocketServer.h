//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_SOCKETSERVER_H
#define BLOCK_CHAIN_SOCKETSERVER_H

#include <thread>

#ifdef _WIN32

#include <winsock2.h>

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* get host by name */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#endif

#include "../Serializer.h"
#include <iostream>
#include <functional>
#include "Socket.h"
#include <chrono>
class Node;
class SocketServer
{
public:
    SocketServer(int port);
    void run(std::function<bool(Socket*, int, Serializer* serializer, Node* node)> func, Serializer* serializer, Node* node);
    void run(Serializer* serializer, Node* node);
    ~SocketServer();
    Socket* master;

protected:
    bool static defaultCallback(Socket* socket, int port, Serializer* serializer, Node* node);
    bool wait(std::function<bool(Socket*, int port, Serializer* serializer, Node* node)> func, Serializer* serializer, Node* node);
    int port;
};

#endif //BLOCK_CHAIN_SOCKETSERVER_H
