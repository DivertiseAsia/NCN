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

void SocketServer::run(std::function<bool(Socket*, int, const Serializer*, Node* node)> func, const Serializer* serializer, Node* node)
{
    while(this->wait(func, serializer, node));
}

void SocketServer::run(Serializer* serializer, Node* node)
{
    this->run(SocketServer::defaultCallback, serializer, node);
}

bool SocketServer::wait(std::function<bool(Socket*, int port, const Serializer* serializer, Node* node)> func, const Serializer* serial, Node* node)
{
    sockaddr_in c_sin = { 0 };
    Socket* socket;
    int sin_size = sizeof c_sin;
    {
        socket = master->_accept(&c_sin, (unsigned int) sin_size);
        if(socket){
            peers.push_back(socket);
            //auto * connection =
            new std::thread(func, socket, port, serial, node);
        }
        //#ifdef _WIN32
    }

    //connection.detach();
    /*#else
    if(!fork())
    {
        func(socket, port, serial, node);
        _exit(0);
    }
    #endif // _WIN32*/
    return socket->socket != 0;
}

bool SocketServer::defaultCallback(Socket* socket, int port, const Serializer*, Node*)
{
    return true;
}
void SocketServer::close(){
    master->_close();
}
SocketServer::~SocketServer()
{
    std::cout << " closed server "<< std::endl;
    peers.clear();

    delete master;
}
