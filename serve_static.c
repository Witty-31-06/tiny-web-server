#include "include.h"
void get_filetype(char *filename, char *filetype)
{
    if(strstr(filename, ".html")) strcpy(filetype, "text/html");
    else if(strstr(filename, ".gif")) strcpy(filetype, "image/gif");
    else if(strstr(filename, ".png")) strcpy(filetype, "image/png");
    else if(strstr(filename, ".jpg")) strcpy(filetype, "image/jpeg");
    else strcpy(filetype, "text/plain");
}

void serve_static(int fd, char *filename, int filesize)
{
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXLINE];
    get_filetype(filename, filetype);
    sprintf(buf, "%s %s %s\r\n", "HTTP/1.0", "200", "OK");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sConnection: close\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-Type: %s\r\n", buf, filetype);
    sprintf(buf, "%s\r\n", buf);
    
    rio_writen(fd, buf, strlen(buf));
    
    printf("Response Headers: ");
    printf("%s", buf);

    //Send response
    srcfd = open(filename, O_RDONLY, 0); //open the requested file in read only mode    
    srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0); //map the file to memory
    close(srcfd);
    rio_writen(fd, srcp, filesize);
    munmap(srcp, filesize); //cleanup
}
