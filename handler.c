#include "include.h"
void handler(int connfd)
{
    printf("INSIDE HANDLER\n");
    int is_static;
    struct stat sbuf; //contains info about files and folders
    char request[MAXLINE], method[MAXLINE], url[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;
    //Read the request
    rio_readinitb(&rio, connfd); //initialize the rio buffer with connfd file descriptor
    rio_readlineb(&rio, request, MAXLINE); //read the client request (from connfd file desc) and store it in request buffer
    printf("Request Headers: ");
    printf("%s", request);
    sscanf(request, "%s %s %s", method, url, version);
    //HTTP request format is like GET url.com/...?args1&args... HTTP/<version>

    //If method is anything else other than get then return 501
    if(strcasecmp(method, "GET") != 0)
    {
        clienterror(connfd, method, "501", "Not implemented", "Our server doesn't implement this method");
        return;
    }

    read_reqesthdrs(&rio); 
    //Neglect rest of the fields in the request. (not necessary for our server)


    //url: /cgi-bin/adder?1&2 -> filename: ./cgi-bin/adder, cgiargs: 1&2
    //static content: url: /index.html -> filename: ./index.html, cgiargs: ""
    is_static = parse_url(url, filename, cgiargs);
    if(stat(filename, &sbuf) < 0) //file not found
    {
        clienterror(connfd, filename, "404", "Not Found", "Server couldn't find the requested file");
        return;
    }

    if(is_static) //Static content requested
    {
        if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode))
        {
            //not a regular file or can't read file
            clienterror(connfd, filename, "403", "Forbidden Access", "Couldn't read file");
            return;
        }
        else serve_static(connfd, filename, sbuf.st_size);
        // exit(1);
    }
    //Dynamic content
    else
    {
        if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode))
        {
            //not a regular file or can't execute file
            clienterror(connfd, filename, "403", "Forbidden Access", "Couldn't execute file");
            return;
        }
        serve_dynamic(connfd, filename, cgiargs);
    }
    
}