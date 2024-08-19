#include "include.h"
void read_reqesthdrs(rio_t *rio)
{
    char buf[MAXLINE];
    rio_readlineb(rio, buf, MAXLINE);
    while(strcmp(buf, "\r\n")) //last line empty
    {
        rio_readlineb(rio, buf, MAXLINE);
        // printf("%s", buf);
    }
    return;
}