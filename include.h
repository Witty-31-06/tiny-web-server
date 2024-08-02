#define _POSIX_C_SOURCE 200112L

#include "ioheader.h"
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

void handler(int fd);
void clienterror(int connfd, char *cause, char *errcode, char *msg, char *desc);
void read_reqesthdrs(rio_t *rio);
void serve_static(int fd, char *filename, int sz);
void serve_dynamic(int fd, char *filename, char * args);
int parse_uri(char uri[], char filename[], char args[]);