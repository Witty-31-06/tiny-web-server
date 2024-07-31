#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include "ioheader.h"


/**
 * @brief Read n bytes from a file descriptor
 * 
 * @param fd 
 * @param usrbuf 
 * @param n 
 * @return ssize_t 
 * @retval -1: error
 * @retval n: number of bytes read
 * @note This function is a wrapper for the read() function. It reads n bytes from the file descriptor fd to the buffer usrbuf.
 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    ssize_t nleft = n; // nleft is the number of bytes left to read
    ssize_t nread; // nread is the number of bytes read
    char *bufp = (char *)usrbuf; // bufp is the pointer to the next byte to store the read byte

    while(nleft > 0) {
        if((nread = read(fd, bufp, nleft)) < 0) {
            if(errno == EINTR) {
                nread = 0;
            } else {
                return -1;
            }
        } else if(nread == 0) {
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}


/**
 * @brief Write n bytes to a file descriptor
 * 
 * @param fd 
 * @param usrbuf 
 * @param n 
 * @return ssize_t 
 * @retval -1: error
 * @retval n: number of bytes written
 * @note This function is a wrapper for the write() function. It writes n bytes from the buffer usrbuf to the file descriptor fd.
 * 
 */
ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    ssize_t nleft = n; // nleft is the number of bytes left to write
    ssize_t nwritten; // nwritten is the number of bytes written
    char *bufp = (char *)usrbuf; // bufp is the pointer to the next byte to write

    while(nleft > 0) {
        if((nwritten = write(fd, bufp, nleft)) <= 0) {
            if(errno == EINTR) {
                nwritten = 0;
            } else {
                return -1;
            }
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

/**
 * @brief  Initialize a rio_t structure
 * 
 * @param rp 
 * @param fd 
 */
void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

/**
 * @brief Read n bytes from a buffered rio_t structure
 * 
 * @param rp 
 * @param usrbuf 
 * @param n 
 * @return ssize_t 
 * @retval -1: error
 * @retval n: number of bytes read
 * @note This function reads n bytes from the buffered rio_t structure rp to the buffer usrbuf.
 */
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;

    while(rp->rio_cnt <= 0) {
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        if(rp->rio_cnt < 0) {
            if(errno != EINTR) {
                return -1;
            }
        } else if(rp->rio_cnt == 0) {
            return 0;
        } else {
            rp->rio_bufptr = rp->rio_buf;
        }
    }

    cnt = n;
    if(rp->rio_cnt < n) {
        cnt = rp->rio_cnt;
    }
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}


/**
 * @brief Read a line from a buffered rio_t structure
 * 
 * @param rp 
 * @param usrbuf 
 * @param maxlen 
 * @return ssize_t 
 */
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    int n, rc;
    char c, *bufp = (char *)usrbuf;

    for(n = 1; n < maxlen; n++) {
        if((rc = rio_read(rp, &c, 1)) == 1) {
            *bufp++ = c;
            if(c == '\n') {
                n++;
                break;
            }
        } else if(rc == 0) {
            if(n == 1) {
                return 0;
            } else {
                break;
            }
        } else {
            return -1;
        }
    }
    *bufp = 0;
    return n - 1;
}


/**
 * @brief Read n bytes from a buffered rio_t structure
 * 
 * @param rp 
 * @param usrbuf 
 * @param n 
 * @return ssize_t 
 */
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = (char *)usrbuf;

    while(nleft > 0) {
        if((nread = rio_read(rp, bufp, nleft)) < 0) {
            return -1;
        } else if(nread == 0) {
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}


