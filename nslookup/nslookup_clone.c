#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#define MAXLINE 8192
int main(int argc, char *argv[])
{
    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;
    if(argc != 2)
    {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // IPv4 only
    hints.ai_socktype = SOCK_STREAM; // TCP



    if((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) //0 if OK
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    // Walk the list and display each IP address associated with the domain
    flags = NI_NUMERICHOST; // Display address string instead of domain name

    for(p = listp; p != NULL; p=p->ai_next)
    {
        getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    }

    freeaddrinfo(listp);
    return 0;
}