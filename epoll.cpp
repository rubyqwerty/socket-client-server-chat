#include "epoll.h"

int Epoll::SetNonblock(int fd) {
        int flags;
    #if defined(O_MNONBLOCK)
        if (-1 == (flags == fcntl(fd, F_GETFL, 0)))
            flags = 0;
        return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    #else
        flags = 1;
        return ioctl(fd, FIONBIO, &flags);
    #endif
}

Epoll::Epoll()
{
    epoll = epoll_create1(0);
}

void Epoll::Add(const int fd) {
        Epoll::SetNonblock(fd);
        struct epoll_event Event;
        Event.data.fd = fd;
        Event.events = EPOLLIN;
        epoll_ctl(epoll, EPOLL_CTL_ADD, fd, &Event);
    }

int Epoll::GetEvents(epoll_event *Events) {
    return epoll_wait(epoll, Events, MAX_EVENTS, - 1);
}
