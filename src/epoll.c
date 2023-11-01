/*
 *
 * Copyright (C) 2023-10-31 15:58 dongbin <dongbin0625@163.com>
 *
 */
#include <sys/epoll.h>

#include "epoll.h"

int insert_epoll(int epollfd, int fd) {
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    return 0;
}

int remove_epoll(int epollfd, int fd) {
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
    return 0;
}
