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
    struct sockaddr_in cliaddr, servaddr;

    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    while(1)
    {
        socklen_t clilen = sizeof(cliaddr);
        int connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);
        pid_t childpid = Fork();

        if(childpid == 0) // child process
        {
            Close(listenfd); // close listening socket
            str_echo(connfd); // process the request
            exit(0);
        }
        Close(connfd); // parent closes connected socket
    }
}
