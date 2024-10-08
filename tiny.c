//Simple Web server that accepts two integers as url params
//and returns their sum
#include "include.h"
#define MAXLINE 8192
//protoypes

int main(int argc, char **argv)
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen; //uint
    struct sockaddr clientaddr;

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    listenfd = open_listenfd(argv[1]); //opening listening socket bound to port
    while(true)
    {
        //Currently the web server supports only one client at a time
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd, &clientaddr, &clientlen);
        getnameinfo(&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Connected with client %s: %s\n", hostname, port);
        if(fork() == 0) //child process
        {
            close(listenfd); //close the listening socket
            handler(connfd);
            close(connfd); //closing the connection
            exit(0);
        }
        // handler(connfd);
        close(connfd); //closing the connection of the parent process
    }
}