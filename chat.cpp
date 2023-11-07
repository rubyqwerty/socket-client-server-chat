#include "chat.h"

Chat::Chat() {
    master_socket.BindSocket(12346);
    master_socket.ListenSocket();
    epoll.Add(master_socket.GetDesriptor());
}

Chat::Chat(int port) {
    master_socket.BindSocket(port);
    master_socket.ListenSocket();
    epoll.Add(master_socket.GetDesriptor());
}

void Chat::MainLoop() {
    while (1) {
        struct epoll_event Events[MAX_EVENTS];

        int N = epoll.GetEvents(Events);

        for (auto i = 0; i < N; ++i) {
            if (Events[i].data.fd == master_socket.GetDesriptor()) {

                struct sockaddr_in client_addr;
                socklen_t size_client_addr;

                int client_socket = master_socket.GetClientDescriptor(client_addr, size_client_addr);
                epoll.Add(client_socket);
        
                if (client_socket > 0) {
                    std::string client_host =  inet_ntoa(client_addr.sin_addr);
                    users.insert({client_socket, client_host});
                    std::string message = "New connection: " + client_host + "\n";
                    for (auto user : users) {
                        Socket::Send(user.first, message);
                    }
                } 
            } else {
                char Buffer[SIZE_BUFFER];
                memset(Buffer, 0 , SIZE_BUFFER);
                int recv_result = recv(Events[i].data.fd, Buffer, SIZE_BUFFER, MSG_NOSIGNAL);
                if ((recv_result == 0) && (errno != EAGAIN)){
                    std::string message = "Disconnection: " + users[Events[i].data.fd] + "\n";

                    users.erase(Events[i].data.fd);

                    for (auto user : users) {
                        Socket::Send(user.first, message);
                    }
                    shutdown(Events[i].data.fd, SHUT_RDWR);
                    close(Events[i].data.fd);
                } else if (recv_result > 0) {
                        std::string message = users[Events[i].data.fd] + "=> " + Buffer + "\n";
                        for (auto user : users) { 
                            if (user.first != Events[i].data.fd)
                                Socket::Send(user.first, message);
                        }
                    }
                }
        }
    }
}

