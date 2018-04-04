//
// Created by default on 3/4/2561.
//

#include "SocketServer.h"

SocketServer::SocketServer(int port): master(NULL)
{
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

void SocketServer::run(std::function<bool(Socket*)> func)
{
    while(this->wait(func));
}

void SocketServer::run()
{
    this->run(SocketServer::defaultCallback);
}

bool SocketServer::wait(std::function<bool(Socket*)> func)
{
    sockaddr_in csin = { 0 };
    int sinsize = sizeof csin;
    Socket* socket = master->_accept(&csin, sinsize);
    #ifdef _WIN32
    std::thread connection (func, socket);
    connection.detach();
    #else
    if(!fork())
    {
        func(socket);
        _exit(0);
    }
    #endif // _WIN32
    return true;
}

bool SocketServer::defaultCallback(Socket* socket)
{
    std::string buffer;
    socket->read(buffer);
    if(buffer.length()){
        auto start = std::chrono::high_resolution_clock::now();
        //TODO: buffer.c_str()
        delete socket;
        auto end = std::chrono::high_resolution_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Request performed in "<< (microseconds/1000.0) << " milliseconds" <<std::endl;
    }

    return true;
}

SocketServer::~SocketServer()
{
    delete master;
}