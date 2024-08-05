#include "include.h"
/**
 * @brief This function parses thr url and puts the filename and args in the respective buffers
 * 
 * @param url 
 * @param filename 
 * @param args 
 * @return int 
 * @note ret val 1 means static content, 0 means dynamic content
 */
int parse_url(char url[], char filename[], char args[])
{
    char *ptr;
    printf("INSIDE PARSE_URL\n");
    //if url contains cgi-bin it's asking for dynamic content
    if(strstr(url, "cgi-bin") == NULL) 
    {
        //Inside if means it contains the string doesn't contain cgi-bin -> serve static
        strcpy(args, "");
        strcpy(filename, ".");
        strcat(filename, url);
        //if uri is .../file.php or xyz.html access that file else access index.html
        if(url[strlen(url) - 1] == '/') strcat(filename, "index.html");

        printf("Filename: %s\n", filename);

        return 1;
        
    }
    else
    {
        //Dynamic content requested

        //cgi-bin/adder?num1&num2
        ptr = strchr(url, '?');
        if(ptr != NULL)
        {
            strcpy(args, ptr+1);  //num1&num2 copied to args
            *ptr = '\0'; //terminate the string url at '?'
        }
        else
        {
            strcpy(args, "");
        }
        strcpy(filename, ".");
        printf("Filename: %s\n", filename);
        strcat(filename, url); //filename = ./cgi-bin/adder
        printf("Filename: %s\n", filename);
        return 0; //0 means dynamic content
    }
}