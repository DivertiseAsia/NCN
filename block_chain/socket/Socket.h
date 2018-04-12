//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_SOCKET_H
#define BLOCK_CHAIN_SOCKET_H


#ifdef _WIN32
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
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#define accept_size unsigned int
#endif


#include <string>
#include <cstring>
#include <iostream>
#include <functional>

class Socket
{
public:
    Socket(std::string, int port);
    Socket(SOCKET s);
    void _bind(sockaddr_in* sin);
    void _listen();
    void _close();
    int _recv(char* buff, int len, int flags, int to);
    int read(std::string& buffer);
    int write(const char* buffer);
    Socket* _accept(sockaddr_in* csin, accept_size size);
    ~Socket();
    SOCKET socket;
    static std::string getIP();
protected:
    fd_set fdset;
    struct timeval tv_timeout;
};
#endif //BLOCK_CHAIN_SOCKET_H
