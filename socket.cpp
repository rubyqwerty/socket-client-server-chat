#include "socket.h"

Socket::Socket() {
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
       
    if (socket_descriptor == -1)
        throw std::runtime_error("Error socket");
}

void Socket::BindSocket(int port) {
    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(port);
    SockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // binding a socket and an address
    if (bind(socket_descriptor, (sockaddr*)&SockAddr, sizeof(SockAddr)) == -1) {
        throw std::runtime_error("Failed bind");
    }
}

void Socket::ListenSocket() {
    // Switching the socket to the connection acceptance mode
    if (listen(socket_descriptor, SOMAXCONN) == -1)
        throw std::runtime_error("Failed listen");
}

int Socket::GetDesriptor() {
    return socket_descriptor;
}

int Socket::GetClientDescriptor(sockaddr_in &client_addr, socklen_t &size_client_addr) {
    return accept(socket_descriptor, (sockaddr*)(&client_addr), &size_client_addr);
}

void Socket::Send(int receiver, std::string message){
    send(receiver, message.c_str(), message.length(), MSG_NOSIGNAL);
}
