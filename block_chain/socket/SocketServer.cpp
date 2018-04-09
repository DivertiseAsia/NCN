//
// Created by default on 3/4/2561.
//

#include "SocketServer.h"

SocketServer::SocketServer(int p): master(nullptr)
{
    port = p;
    #ifdef _WIN32
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    #endif // _WIN32
    master = new Socket(socket(AF_INET , SOCK_STREAM , 0));
    sockaddr_in sin = { 0 };
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    master->_bind(&sin);
    master->_listen();

    std::cout << "Server listening on port " << port << std::endl;
}

void SocketServer::run(std::function<bool(Socket*, int, Serializer*, Node* node)> func, Serializer* serializer, Node* node)
{
    while(this->wait(func, serializer, node));
}

void SocketServer::run(Serializer* serializer, Node* node)
{
    this->run(SocketServer::defaultCallback, serializer, node);
}

bool SocketServer::wait(std::function<bool(Socket*, int port, Serializer* serializer, Node* node)> func, Serializer* serial, Node* node)
{
    sockaddr_in c_sin = { 0 };
    int sin_size = sizeof c_sin;
    Socket* socket = master->_accept(&c_sin, sin_size);
    //#ifdef _WIN32
    std::thread connection (func, socket, port, serial, node);
    connection.detach();
    /*#else
    if(!fork())
    {
        func(socket, port, serial, node);
        _exit(0);
    }
    #endif // _WIN32*/
    return true;
}

bool SocketServer::defaultCallback(Socket* socket, int port, Serializer* serializer, Node* node)
{
    std::string buffer;
    socket->read(buffer);
    if(buffer.length()){
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "Request received on port " << port << " : " << buffer <<std::endl;
        delete socket;
        auto end = std::chrono::high_resolution_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Request performed in "<< (microseconds/1000.0) << " milliseconds" <<std::endl;
    }

    return true;
}

SocketServer::~SocketServer()
{
    std::cout << " closed "<< std::endl;
    delete master;
}
