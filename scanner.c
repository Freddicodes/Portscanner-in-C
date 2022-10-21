//
// Created by Jan on 21.10.22.
//

#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>

#define IP_LENGTH 16
#define PORT_LENGTH 6

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Please provide the following arguments: server_ip, start_port, end_port\n");
        exit(1);
    }

    char ip[IP_LENGTH] = {0};
    strncpy(ip, argv[1], IP_LENGTH);

    long first_port = strtol(argv[2], NULL, 10);
    if (first_port < 0 || errno == EINVAL || errno == ERANGE) {
        printf("Problem resolving port number\n");
    }

    long last_port = strtol(argv[3], NULL, 10);
    if (last_port < first_port || errno == EINVAL || errno == ERANGE) {
        printf("Problem resolving port number\n");
    }

    struct sockaddr_in sa;
    int sock, err;
    sock = err = -1;

    strncpy((char *) &sa, "", sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ip);

    for (; first_port <= last_port; ++first_port) {
        printf("scanning port %li\n", first_port);

        sa.sin_port = htons(first_port);
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (socket < 0) {
            printf("Problem with port\n");
            exit(1);
        }

        err = connect(sock, (struct sockaddr*)&sa, sizeof sa);

        if (err < 0) {
            fflush(stdout);
        } else {
            printf("Port %li is open\n", first_port);
        }
        close(sock);
    }
    fflush(stdout);
    return 0;
}