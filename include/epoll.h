/*
 * epoll.h
 * Copyright (C) 2023 dongbin <dongbin0625@163.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef __EPOLL_H__
#define __EPOLL_H__

#include <stdio.h>
#include <sys/epoll.h>

int insert_epoll(int epollfd,int fd);
int remove_epoll(int epollfd,int fd);

#endif /* !__EPOLL_H__ */
