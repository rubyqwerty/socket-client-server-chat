#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#define MAX_EVENTS 32

class Epoll {
private:
    int epoll;
    static int SetNonblock(int fd);
public:
    Epoll();
    void Add(const int fd);
    int GetEvents (epoll_event* Events);

};