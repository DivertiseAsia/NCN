//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_SOCKET_SERVER_H
#define BLOCK_CHAIN_SOCKET_SERVER_H

#include <thread>

#ifdef _WIN32
#ifndef close_socket
#define close_socket(s) closesocket(s)
#endif // close_socket
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* get host by name */
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#ifndef close_socket
#define close_socket(s) close(s)
#endif // close_socket
typedef int SOCKET;
/*typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;*/
#endif

#include "../serialization/Serializer.h"
#include <iostream>
#include <functional>
#include "Socket.h"
#include <chrono>
class Node;

/**
 *  The class that listen to the port
 *
 *  @author Mathieu Lochet
 *  @version 3
 */
class SocketServer
{
public:

    /**
     *  The constructor that generates the connection
     *  on the given port
     *  @see Socket
     *
     *  @param port the port the listen to
     */
    explicit SocketServer(int port);

    /**
     *  Run the server with a given callback
     *  @see Socket
     *  @see Serializer
     *  @see Node
     *
     *  @param func the callback to use with each client. The callback must have a prototype such as "bool (Socket*, const Serializer*, Node*)"
     *  @param serializer the serializer to use to parse packets
     *  @param node the client that uses the server
     */
    void run(std::function<bool(Socket*, int, const Serializer* serializer, Node* node)> func, const Serializer* serializer, Node* node);

    /**
     *  Run the server with a default callback
     *  @deprecated
     *  @see Serializer
     *  @see Node
     *
     *  @param serializer the serializer to use to parse packets
     *  @param node the client that uses the server
     */
    void run(Serializer* serializer, Node* node);

    /**
     *  The destructor closes the connection with the other peers
     */

    virtual ~SocketServer();

    /**
     *  Closes the connection with the other peers
     */
    void close();
private:

    /**
     *  The master socket of the server, used to connect
     *  with other sockets
     */
    Socket* master;

    /**
     *  The default callback that does nothing
     *  @deprecated
     *  @see Socket
     *  @see Serializer
     *  @see Node
     *
     *  @param socket the socket of the peer
     *  @param serializer the serializer to use to unserialize the messages
     *  @param node the client that receive the messages
     *  @return true
     */
    bool static defaultCallback(Socket* socket, int port, const Serializer* serializer, Node* node);

    /**
     *  Wait for a connection and calls the callback each time
     *  @see Socket
     *  @see Serializer
     *  @see Node
     *
     *  @param func the callback to use with each client. The callback must have a prototype such as "bool (Socket*, const Serializer*, Node*)"
     *  @param serializer the serializer to use to parse packets
     *  @param node the client that uses the server
     *  @return true if the server runs, false otherwise
     */
    bool wait(std::function<bool(Socket*, int port, const Serializer* serializer, Node* node)> func, const Serializer* serializer, Node* node);

    /**
     *  The port on which to listen to
     */
    int port;

    /**
     *  The list of peers connected to the server
     */
    std::vector<Socket*> peers;
};

#endif //BLOCK_CHAIN_SOCKET_SERVER_H
