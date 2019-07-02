#include "socket.h"
#include "base.h"

#define SERV_PORT 10000

void str_cli(FILE *fp, int sockfd)
{
    int maxfd, stdineof;
    fd_set rset;
    char buf[MAXLINE];
    int n;

    stdineof = 0;
    FD_ZERO(&rset);
    while (1)
    {
        if (stdineof == 0)
        {
            FD_SET(fileno(fp), &rset);
        }
        FD_SET(sockfd, &rset);
        maxfd = max(fileno(fp), sockfd) + 1;
        Select(maxfd, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset)) // socket is readable
        {
            if ((n = Read(sockfd, buf, MAXLINE)) == 0)
            {
                if (stdineof == 1)
                {
                    return; // normal termination
                }
                else
                {
                    printf("str_cli: server terminated prematurely\n");
                    exit(-1);
                }
            }
            Write(fileno(stdout), buf, n);
        }

        if (FD_ISSET(fileno(fp), &rset)) // input is readable
        {
            if ((n = Read(fileno(fp), buf, MAXLINE)) == 0)
            {
                stdineof = 1;
                ShutDown(sockfd, SHUT_WR); // send FIN
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            Writen(sockfd, buf, n);
        }
    }
}

int main(int argc, char **argv)
{
    struct sockaddr_in servaddr;

    if(argc != 2)
    {
        printf("usage: tcpcli <IPaddress>\n");
        exit(-1);
    }

    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd); // do it all

    exit(0);
}
