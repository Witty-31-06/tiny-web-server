#include "include.h"
/**
 * @brief The clienterror function sends an error message to the client
 *      using the provided arguments.
 * 
 * @param connfd file descriptor of the connection
 * @param cause Cause of Error
 * @param errcode Error code to return
 * @param msg Short message
 * @param desc Description of the error 
 */
void clienterror(int connfd, char *cause, char *errcode, char *msg, char *desc)
{
    char buf[MAXLINE], body[MAXLINE];

    //HTTP Response BODY
    sprintf(body, "<html> <title> Error </title>");
    sprintf(body, "%s<body bgcolor = ""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errcode, msg);
    sprintf(body, "%s<p>%s: %s</p>\r\n", body, desc, cause);
    sprintf(body, "%s<hr><em>The web server</em></hr>\r\n", body);

    sprintf(buf,    "HTTP/1.0 %s %s\r\n", errcode, msg);
    rio_writen(connfd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    rio_writen(connfd, buf, strlen(buf));
    sprintf(buf, "Content-length: %lu\r\n\r\n", strlen(body));
    rio_writen(connfd, buf, strlen(buf));
    rio_writen(connfd, body, strlen(body));
    return;
}