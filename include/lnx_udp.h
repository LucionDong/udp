/*
 * lnx_udp.h
 * Copyright (C) 2023 dongbin <dongbin0625@163.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef __LNX_UDP_H__
#define __LNX_UDP_H__

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int init_udp(int *plistener, char *ip, int port, struct sockaddr_in *addr);
int recv_udp(int *plistener, char *ip, struct sockaddr_in *addr);
int send_udp(int *plistener, char *ip, int port,char*buf);

#endif /* !__LNX_UDP_H__ */
