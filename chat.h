#include "socket.h"
#include "epoll.h"
#include <map>

class Chat {
private:
    Socket master_socket;
    Epoll epoll;
    std::map<int, std::string> users;

public:
    Chat();
    Chat(int);
    void MainLoop();
};