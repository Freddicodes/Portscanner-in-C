//
// Created by Jan on 21.10.22.
//

#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/fcntl.h>

#include "scanner.h"

int open_ports[65535] = {0};

int start(char **argv) {

    char ip[IP_LENGTH] = {0};
    struct sockaddr_in sa;
    int sock;
    fd_set fdset;
    struct timeval tv;

    // copy the ip address
    strncpy(ip, argv[1], IP_LENGTH);

    // turning arguments to port number
    long first_port = strtol(argv[2], NULL, 10);
    if (first_port < 0 || errno == EINVAL || errno == ERANGE) {
        printf("Problem resolving start port\n");
        return -1;
    }

    long last_port = strtol(argv[3], NULL, 10);
    if (last_port < first_port || errno == EINVAL || errno == ERANGE) {
        printf("Problem resolving end port\n");
        return ERROR;
    }

    // set address family and resolve ip address
    sa.sin_family = AF_INET;
    if (inet_pton(AF_INET, argv[1], &sa.sin_addr.s_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return ERROR;
    }

    // start iterating ports
    for (; first_port <= last_port; ++first_port) {
        sa.sin_port = htons(first_port);

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("Problem with port\n");
            return ERROR;
        }

        // set socket to no blocking
        fcntl(sock, F_SETFL, O_NONBLOCK);

        // try connection
        connect(sock, (struct sockaddr *) &sa, sizeof sa);

        FD_ZERO(&fdset);
        FD_SET(sock, &fdset);
        tv.tv_sec = 10;             /* 10 second timeout */
        tv.tv_usec = 0;

        if (select(sock + 1, NULL, &fdset, NULL, &tv) == 1)
        {
            int so_error;
            socklen_t len = sizeof so_error;

            getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);

            if (so_error == 0) {
                printf("%s:%ld\tis", argv[1], first_port);
                open_ports[first_port] = 1;
                printf(GRN);
                printf(" open\n");
                printf(RST);
            } else {
                printf("%s:%ld\tis ", argv[1], first_port);
                printf(RED);
                printf("closed\n");
                printf(RST);
            }
        }
        close(sock);
    }
    fflush(stdout);

    return SUCCESS;
}
