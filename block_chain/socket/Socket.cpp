//
// Created by default on 3/4/2561.
//

#include "Socket.h"
SOCKET createSocket(){
    return socket(AF_INET , SOCK_STREAM , 0);
}

Socket::Socket(std::string address , int port)
{
    struct sockaddr_in server;
    //Create socket
    socket = createSocket();
    if (socket == -1)
        #ifdef _WIN32
        std::cout << WSAGetLastError() << std::endl;
        #else
        perror("Could not create socket");
        #endif // _WIN32

    //setup address structure
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;

        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL) {
            #ifdef _WIN32
            std::cout << WSAGetLastError() << std::endl;
            #else
            herror("gethostbyname");
            #endif // _WIN32
            //gethostbyname failed
        }

        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];
            break;
        }
    }

    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }

    server.sin_family = AF_INET;
    server.sin_port = htons( port );

    //Connect to remote server
    /*
    if (
    {
        perror("port connect failed. Error");
        std::cout << "Test port "<< connect(socket, (struct sockaddr *)&server , sizeof(server)) << std::endl;
    }
     */
    connect(socket, (struct sockaddr *)&server , sizeof(server));
}

Socket::Socket(SOCKET s): socket(s)
{
    if(socket == INVALID_SOCKET)
    {
        #ifdef _WIN32
        std::cout << WSAGetLastError() << std::endl;
        #else
        perror("Invalid socket");
        #endif // _WIN32
        exit(errno);
    }
}

void Socket::_bind(sockaddr_in* sin){
    if(bind (socket, (sockaddr *) sin, sizeof (*sin)) == SOCKET_ERROR)
    {
        #ifdef _WIN32
        std::cout << WSAGetLastError() << std::endl;
        #else
        perror("Bind failed");
        #endif // _WIN32
        exit(errno);
    }
}

void Socket::_listen(){
    if(listen(socket, 32) == SOCKET_ERROR)
    {
        #ifdef _WIN32
        std::cout << WSAGetLastError() << std::endl;
        #else
        perror("Listening failed");
        #endif // _WIN32
        exit(errno);
    }
}

Socket* Socket::_accept(sockaddr_in* c_sin, accept_size size){
    return new Socket(accept(socket, (sockaddr*)c_sin, &size));
}

void Socket::_close(){
    closesocket(socket);
}

int Socket::read(std::string& buffer){
    FD_ZERO(&fdset);
    tv_timeout.tv_sec = 0;
    tv_timeout.tv_usec = 500;
    FD_SET(socket, &fdset);
    buffer = "";
    char buff[2];
    do
    {
        //if(
            if(recv(socket, buff, 1, 0) > 0)
            {
                buffer += buff[0];select(socket + 1, &fdset, nullptr, nullptr, &tv_timeout) ;
            }
            else
                return 0;
    }
    while (FD_ISSET(socket, &fdset));
    FD_CLR(socket, &fdset);
    return buffer.size();
}

int Socket::write(const char* buffer){
    return (int)send(socket, buffer, strlen(buffer), 0);
}

Socket::~Socket(){
    std::cout<<"Closed socket"<< std::endl;
    closesocket(socket);
}
