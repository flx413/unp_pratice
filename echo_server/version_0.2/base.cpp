#include "base.h"

ssize_t readn(int fd, void *vptr, size_t n)
{
    char *ptr = (char*)vptr;
    size_t nleft = n;
    ssize_t nread;

    while(nleft > 0)
    {
        if((nread = read(fd, ptr, nleft)) < 0)
        {
            if(errno == EINTR)
            {
                nread = 0; // need call read() again
            }
            else
            {
                return -1;
            }
        }
        else if(nread == 0)
        {
            break; // EOF
        }
        nleft -= nread;
        ptr += nread;
    }

    return (n - nleft);
}

ssize_t writen(int fd, const void *vptr, size_t n)
{
    const char* ptr = (char*)vptr;
    size_t nleft = n;
    ssize_t nwritten;

    while(nleft > 0)
    {
        if((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if(nwritten < 0 && errno == EINTR)
            {
                nwritten = 0; // need call write() again
            }
            else
            {
                return -1;
            }
        }
        nleft -= nwritten;
        ptr += nwritten;
    }

    return n;
}

static ssize_t my_read(int fd, char *ptr)
{
    if(read_cnt <= 0)
    {
again:
        if((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
        {
            if(errno == EINTR)
            {
                goto again;
            }
            else
            {
                return -1;
            }
        }
        else if(read_cnt == 0)
        {
            return 0;
        }
        read_ptr = read_buf;
    }

    read_cnt--;
    *ptr = *read_ptr++;

    return 1;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
    char *ptr = (char*)vptr;
    ssize_t n, rc;
    char c;

    for(n = 1; n < maxlen; n++)
    {
        if((rc = my_read(fd, &c)) == 1)
        {
            *ptr++ = c;
            if(c == '\n')
            {
                break; // newline is stored, like fgets()
            }
        }
        else if(rc == 0)
        {
            *ptr = 0;
            return (n - 1); // EOF, n - 1 bytes were read
        }
        else
        {
            return -1; // error, errno set by read()
        }
    }

    *ptr = 0; // null terminate like fgets()

    return n;
}

ssize_t Readn(int fd, void *ptr, size_t nbytes)
{
    ssize_t n = readn(fd, ptr, nbytes);
    if(n < 0)
    {
        printf("readn error\n");
        exit(-1);
    }

    return n;
}

void Writen(int fd, void *ptr, size_t nbytes)
{
    if(writen(fd, ptr, nbytes) != nbytes)
    {
        printf("writen error\n");
        exit(-1);
    }
}

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
    ssize_t n = readline(fd, ptr, maxlen);
    if(n < 0)
    {
        printf("readline error\n");
        exit(-1);
    }

    return n;
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
    ssize_t n = read(fd, ptr, nbytes);
    if(n == -1)
    {
        printf("read error\n");
        exit(-1);
    }

    return n;
}

void Write(int fd, void *ptr, size_t nbytes)
{
    if(write(fd, ptr, nbytes) != nbytes)
    {
        printf("write error\n");
        exit(-1);
    }
}

int Open(const char *pathname, int flags, mode_t mode)
{
    int fd = open(pathname, flags, mode);
    if(fd == -1)
    {
        printf("open file %s errno\n", pathname);
        exit(-1);
    }

    return fd;
}

void Close(int fd)
{
    if(close(fd) == -1)
    {
        printf("close error\n");
        exit(-1);
    }
}

void Fputs(const char *ptr, FILE *stream)
{
    if(fputs(ptr, stream) == EOF)
    {
        printf("fputs error\n");
        exit(-1);
    }
}

char* Fgets(char *ptr, int n, FILE *stream)
{
    char *rptr = fgets(ptr, n, stream);
    if(rptr == NULL && ferror(stream))
    {
        printf("fgets error\n");
        exit(-1);
    }

    return rptr;
}

pid_t Fork()
{
    pid_t pid = fork();
    if(pid == -1)
    {
        printf("fork error\n");
        exit(-1);
    }

    return pid;
}
