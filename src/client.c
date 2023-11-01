/*
 *
 * Copyright (C) 2023-10-31 15:05 dongbin <dongbin0625@163.com>
 *
 */
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#include "epoll.h"
#include "lnx_udp.h"
#define MAX_MONITOR 1024
#define CHECK_RET(ret, msg) \
    {                       \
        if (ret == -1) {    \
            perror(msg);    \
            return 0;       \
        }                   \
    }

#define CHECK_ARGC(argc, num)       \
    {                               \
        if (argc != num) {          \
            printf("error argc\n"); \
            return -1;              \
        }                           \
    }

int main(int argc, char **argv) {
    CHECK_ARGC(argc, 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret = 0;
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_family = AF_INET;
    // ret = sendto(sockfd, "test", 4, 0, (struct sockaddr *) &addr, sizeof(addr));

    int epfd = epoll_create(1);

    insert_epoll(epfd, sockfd);
    insert_epoll(epfd, STDIN_FILENO);
    struct epoll_event ready_set[MAX_MONITOR];

    while (1) {
        int ready_num = epoll_wait(epfd, ready_set, MAX_MONITOR, -1);
        int i;
        for (i = 0; i < ready_num; ++i) {
            if (ready_set[i].data.fd == sockfd) {
                char buf[1024] = {0};
                recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);

                printf("recv buf is %s\n", buf);
            }
            if (ready_set[i].data.fd == STDIN_FILENO) {
                char buf[1024] = {0};
                ret = read(STDIN_FILENO, buf, sizeof(buf));
                //   if (ret == 0) {
                // sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) &addr, sizeof(addr));
                // break;
                //   }
                printf("send buf: %s\n", buf);
                ret = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) &addr, sizeof(addr));
                printf("sendto ret: %d\n", ret);
            }
        }
    }
    return 0;
}
