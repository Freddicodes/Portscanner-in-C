//
// Created by Jan on 21.10.22.
//

#ifndef PORTSCANNER_IN_C_SCANNER_H
#define PORTSCANNER_IN_C_SCANNER_H


#define IP_LENGTH 16

#define SUCCESS 1
#define ERROR -1

#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define RST "\033[0m"

extern int open_ports[];

int start(char ** argv);



#endif
