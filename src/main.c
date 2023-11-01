/*
 *
 * Copyright (C) 2023-10-31 15:05 dongbin <dongbin0625@163.com>
 *
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "epoll.h"
#include "lnx_udp.h"
#define CHECK_RET(ret, msg) \
    {                       \
        if (ret == -1) {    \
            perror(msg);    \
            return 0;       \
        }                   \
    }

int main(int argc, char **argv) {
    int sockfd;
    int ret = 0;
    struct sockaddr_in addr;

    int epfd = epoll_create(1);

    if ((ret = init_udp(&sockfd, argv[1], 1234, &addr)) == -1) {
        perror("init_udp");
        return -1;
    }

    insert_epoll(epfd, sockfd);
    insert_epoll(epfd, STDIN_FILENO);
    struct epoll_event ready_set[1024];

    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    char buf[1024] = {0};
	ssize_t sret = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *) &client_addr, &client_addr_size);

    while (1) {
        int ready_num = epoll_wait(epfd, ready_set, 1024, -1);
        for (int i = 0; i < ready_num; ++i) {
            if (ready_set[i].data.fd == sockfd) {
                printf("sockfd\n");
                char buf[1024] = {0};
                recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *) &client_addr, NULL);

                printf("client_addr.sin_addr %s, port = %d\n", inet_ntoa(client_addr.sin_addr),
                       ntohs(client_addr.sin_port));
                printf("recv buf is %s\n", buf);
            }
            if (ready_set[i].data.fd == STDIN_FILENO) {
                printf("STDIN_FILENO\n");
                bzero(buf, sizeof(buf));
                ret = read(STDIN_FILENO, buf, sizeof(buf));

                if (ret == 0) {
                    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) &client_addr, client_addr_size);
                    break;
                }
                printf("send buf: %s\n", buf);
                ret = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) &client_addr, client_addr_size);
                printf("sendto ret: %d\n", ret);
            }
        }
    }
    return 0;
}
