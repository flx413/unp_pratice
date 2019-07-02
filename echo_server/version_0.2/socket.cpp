#include "socket.h"

int Socket(int family, int type, int protocol)
{
    int n = socket(family, type, protocol);
    if(n < 0)
    {
        printf("socket error\n");
        exit(-1);
    }

    return n;
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if(connect(fd, sa, salen) < 0)
    {
        printf("connect error\n");
        exit(-1);
    }
}

void Listen(int fd, int backlog)
{
    if(listen(fd, backlog) < 0)
    {
        printf("listen error\n");
        exit(-1);
    }
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if(bind(fd, sa, salen) < 0)
    {
        printf("bind error\n");
        exit(-1);
    }
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n = accept(fd, sa, salenptr);
    if(n < 0)
    {
        printf("accept error\n");
        exit(-1);
    }

    return n;
}

void Inet_pton(int family, const char *strptr, void *addrptr)
{
    if(inet_pton(family, strptr, addrptr) < 0)
    {
        printf("inet_pton error for %s\n", strptr);
        exit(-1);
    }
}

const char* Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
    const char *ptr = inet_ntop(family, addrptr, strptr, len);
    if(ptr == NULL)
    {
        printf("inet_ntop error\n");
        exit(-1);
    }

    return ptr;
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
    int n = select(nfds, readfds, writefds, exceptfds, timeout);
    if (n < 0)
    {
        printf("select error\n");
        exit(-1);
    }

    return n; // can return 0 on timeout
}

int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout)
{
    int n = poll(fdarray, nfds, timeout);
    if (n < 0)
    {
        printf("poll error\n");
        exit(-1);
    }

    return n;
}

void ShutDown(int fd, int how)
{
    if (shutdown(fd, how) < 0)
    {
        printf("shutdown error\n");
        exit(-1);
    }
}