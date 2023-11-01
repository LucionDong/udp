/*
 *
 * Copyright (C) 2023-10-31 14:31 dongbin <dongbin0625@163.com>
 *
 */

#include "lnx_udp.h"

int init_udp(int *plistener, char *ip, int port, struct sockaddr_in *addr) {
    *plistener = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (*plistener == -1) {
        perror("socket");
        return -1;
    }

    // struct sockaddr_in addr;
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    inet_aton(ip, &addr->sin_addr);

    int reuse = 1;
    setsockopt(*plistener, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));

    if (bind(*plistener, (struct sockaddr *) addr, sizeof(*addr)) == -1) {
        perror("bind");
        return -1;
    }
    return 0;
}

int recv_udp(int *plistener, char *ip, struct sockaddr_in *addr) {
    // struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buf[1024] = {0};
    int ret = recvfrom(*plistener, buf, sizeof(buf), 0, (struct sockaddr *) &addr, &len);
    printf("buf: %s\n", buf);
    if (ret < 0) {
        perror("recvfrom error");
        return -1;
    }
    return 0;
}

int send_udp(int *plistener, char *ip, int port, char *buf) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    int ret =
        sendto(*plistener, buf, strlen(buf), 0, (struct sockaddr *) &addr, (socklen_t) sizeof(struct sockaddr_in));
    printf("buf: %s\n", buf);
    printf("ret: %d\n", ret);

    if (ret < 0) {
        perror("sendto");
        return -1;
    }
    return 0;
}
