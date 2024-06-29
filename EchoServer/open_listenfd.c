#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <netdb.h>
#include <string.h> //for memset

/**
 * @brief 
 * 
 * @param port 
 * @return int 
 */
int open_listenfd(char *port)
{
    struct addrinfo hints, *listp, *p;
    int listenfd, optval = 1;

    /*Get a list of */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM; /*Accept connections*/
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; /*On any IP address*/
    hints.ai_flags |= AI_NUMERICSERV; /*Using port number*/
    getaddrinfo(NULL, port, &hints, &listp);

    /*Walk the list for one that we can bind to*/
    for(p = listp; p; p = p->ai_next)
    {
        /*Create a socket descriptor*/
        if((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue; /*Socket failed, try the next*/

        /*Eliminates "Address already in use" error from bind*/
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

        /*Bind the descriptor to the address*/
        if(bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break; /*Success*/

        close(listenfd); /*Bind failed, try the next*/
    }
    freeaddrinfo(listp);
    if(!p) /*No address worked*/
        return -1;
    if(listen(listenfd, 1024) < 0)
    {
        close(listenfd);
        return -1;
    }
    return listenfd;
}