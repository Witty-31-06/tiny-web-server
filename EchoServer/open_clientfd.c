#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <netdb.h>
#include <string.h> //for memset
#include <unistd.h>
/**
 * @brief This function is used to open a client connection to a server
 * @param hostname The hostname of the server
 * @param port The port number of the server
 * @return The file descriptor of the client connection, -1 on error
 * @note This function is a wrapper for the getaddrinfo, socket, and connect functions
 */
int open_clientfd(char *hostname, char *port)
{
    int clientfd;
    struct addrinfo hints, *listp, *p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM; //for TCP
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG; //numeric port, address config
    getaddrinfo(hostname, port, &hints, &listp);
    for (p = listp; p; p = p->ai_next)
    {
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)//attempting to connect
            break;
        close(clientfd);
    }
    freeaddrinfo(listp);
    return (p == NULL) ? -1 : clientfd;
}