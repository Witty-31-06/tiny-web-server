#ifndef NETINCLUDE_H 
#define NETINCLUDE_H 
#define _POSIX_C_SOURCE 200112L

#include "ioheader.h" //for rio_t
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdlib.h>
void handler(int fd);
void clienterror(int connfd, char *cause, char *errcode, char *msg, char *desc);
void read_reqesthdrs(rio_t *rio);
void serve_static(int fd, char *filename, int sz);
void serve_dynamic(int fd, char *filename, char * args);
int parse_url(char uri[], char filename[], char args[]);
#endif