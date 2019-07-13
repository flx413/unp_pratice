#include "socket.h"
#include "base.h"

#define SERV_PORT 10000
#define LISTENQ   5

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];

again:
    while((n = read(sockfd, buf, MAXLINE)) > 0)
    {
        Writen(sockfd, buf, n);
    }

    if(n < 0 && errno == EINTR)
    {
        goto again;
    }
    else if(n < 0)
    {
        printf("str_echo: read error\n");
    }
}

int main(int argc, char **argv)
{
    int i, maxi, maxfd, listenfd, connfd, sockfd;
    int nready, client[FD_SETSIZE];
    ssize_t n;
    fd_set rset, allset;
    char buf[MAXLINE];
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    maxfd = listenfd; // initialize
    maxi = -1;  // index into client[] array
    for (i = 0; i < FD_SETSIZE; i++)
    {
        client[i] = -1; // -1 indicates avaliable entry
    }

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    while (1)
    {
        rset = allset; // structure assignment
        nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &rset)) // new client connection
        {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);

            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i] < 0)
                {
                    client[i] = connfd; // save descriptor
                    break;
                }
            }

            if (i == FD_SETSIZE)
            {
                printf("too many clients\n");
                exit(-1);
            }

            FD_SET(connfd, &allset); // add new descriptor to set
            if (connfd > maxfd)
            {
                maxfd = connfd; // for select
            }

            if (i > maxi)
            {
                maxi = i; // max index in client[] array
            }

            if (--nready <= 0)
            {
                continue; // no more readable descriptors
            }
        }

        for (i = 0; i <= maxi; i++) // check all clients  for data
        {
            if ((sockfd = client[i]) < 0)
            {
                continue;
            }

            if (FD_ISSET(sockfd, &rset))
            {
                if ((n = Read(sockfd, buf, MAXLINE)) == 0) // connection closed by client
                {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                {
                    Writen(sockfd, buf, n);
                }

                if (--nready == 0)
                {
                    break; // no more readable descriptors
                }
            }
        }
    }
}
