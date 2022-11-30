//
// Created by Jan on 30.10.22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"

int main(int argc, char **argv) {
    // help menu
    if (argc < 4 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        printf("Please provide the following arguments: server_ip  start_port  end_port\n");
        exit(1);
    }

    printf("Starting scan for %s", argv[1]);
    printf("\n\n");
    printf("IP : PORT : STATE");
    printf("\n\n");

    if (!start(argv)) {
        printf("An error occurred\n");
    }

    printf("All open ports:");
    printf(GRN);
    for (int i = 0; i < 65535 - 1 ; i++)
    {
        open_ports[i] == 1 ? printf("%i, ", i) : 1;
    }
    open_ports[65535 - 1] == 1 ? printf("%i, ", 65534) : 1;
    printf(RST);
    
    return 0;
}
