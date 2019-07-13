#include "socket.h"
#include "base.h"

#define SERV_PORT 10000

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while(Fgets(sendline, MAXLINE, fp) != NULL)
    {
        Writen(sockfd, sendline, strlen(sendline));
        if(Readline(sockfd, recvline, MAXLINE) == 0)
        {
            printf("str_cli: server terminated prematurely\n");
            exit(-1);
        }
        Fputs(recvline, stdout);
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
