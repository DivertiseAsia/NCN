//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_SOCKET_H
#define BLOCK_CHAIN_SOCKET_H


#ifdef _WIN32
#ifndef close_socket
#define close_socket(s) closesocket(s)
#endif // close_socket
#include <winsock2.h>
#define accept_size int
#else

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* get host by name */
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#ifndef close_socket
#define close_socket(s) close(s)
#endif // close_socket
typedef int SOCKET;
/*
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;*/
#define accept_size unsigned int
#endif


#include <string>
#include <cstring>
#include <iostream>
#include <functional>

/**
 *  @class Socket "block_chain/utils/socket/Socket.h"
 *  The class that listen to the port
 *
 *  @author Mathieu Lochet
 *  @version 3
 */
class Socket
{
    friend class SocketServer;
public:

    /**
     *  The constructor that generates a socket
     *  with a given IP and port
     *
     *  @param i the IP to connect to
     *  @param port the port the connect to
     */
    Socket(std::string i, int port);

    /**
     *  The constructor that generates a socket
     *  with a SOCKET value
     *
     *  @param s the SOCKET value
     */
    explicit Socket(SOCKET s);

    /**
     *  Bind the socket to a given address so
     *  it can listen to connections
     *
     *  @param sin the given address
     */
    void _bind(sockaddr_in* sin);

    /**
     *  Listen to connections
     */
    void _listen();

    /**
     *  Close the socket connection
     */
    void _close();

    /**
     *  Read values from the socket when a packet in received
     *
     *  @param buffer the buffer in which to write the packet
     *  @return 1 if success, 0 if failure
     */
    int read(std::string& buffer);

    /**
     *  Write a packet to a given packet
     *
     *  @param buffer the buffer to send to the peer
     *  @return 1 if success, 0 if failure
     */
    int write(const char* buffer);

    /**
     *  Wait and accepts a connection on the server
     *
     *  @param csin a socket address
     *  @param size the size of the socket address
     *  @return 1 if success, 0 if failure
     */
    Socket* _accept(sockaddr_in* csin, accept_size size);

    /**
     *  Close the socket connection
     */
    ~Socket();

    /**
     *  Generate the IP of the computer
     *
     *  @return The IP of the computer
     */
    static std::string getIP();
private:

    /**
     *  The fdset to assure timeout for reading
     */
    fd_set fdset;

    /**
     *  The given timeout before shutting the connection down
     */
    struct timeval tv_timeout;

    /**
     *  The real SOCKET value
     */
    SOCKET socket;
};
#endif //BLOCK_CHAIN_SOCKET_H
