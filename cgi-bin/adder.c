#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 8192
int main(void)
{
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1=0, n2=0;

    // Extract the two arguments
    if ((buf = getenv("QUERY_STRING")) != NULL) {
        //Args are passed in url as url.com?param1&param2
        p = strchr(buf, '&');
        *p = '\0';
        strcpy(arg1, buf);
        strcpy(arg2, p+1);
        n1 = atoi(arg1);
        n2 = atoi(arg2);
    }

    //HTTP Response Body
    sprintf(content, "QUERY_STRING=%s", buf);
    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%s<p>THE Internet addition portal.</p>\r\n", content);
    sprintf(content, "%s<p>The answer is: %d + %d = %d</p>\r\n", content, n1, n2, n1 + n2);
    sprintf(content, "%s<p>Thanks for visiting!</p>\r\n", content);

    // Generate the HTTP response
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout); 
    exit(0);
}