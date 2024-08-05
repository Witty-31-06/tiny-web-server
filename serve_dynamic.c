#include "include.h"
extern char **environ;
void serve_dynamic(int connfd, char *filename, char *args)
{
    char buf[MAXLINE], *emptylist[] = {NULL};
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    rio_writen(connfd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    rio_writen(connfd, buf, strlen(buf));
    //We fork so that parent can continue handling other clients
    if(fork() == 0) //in child pid = 0
    {
        setenv("QUERY_STRING", args, 1);
        dup2(connfd, STDOUT_FILENO); //Writing to stdout will write to the client
        execve(filename, emptylist, environ);
    }
    wait(NULL);
}