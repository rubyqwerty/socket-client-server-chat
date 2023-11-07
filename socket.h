#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <cstring>
#include <arpa/inet.h>
#include <exception>

#define SIZE_BUFFER 1024

class Socket {
public:
    Socket();
    void BindSocket(int port);
    void ListenSocket();
    int GetDesriptor();
    int GetClientDescriptor(sockaddr_in& client_addr, socklen_t& size_client_addr);
    static void Send(int receiver, std::string message);
private:
    int socket_descriptor = -1;
};