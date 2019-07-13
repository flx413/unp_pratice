#include "common.h"

#define MAXLINE 80

#define min(a,b) ((a) < (b) ? (a) : (b)) 
#define max(a,b) ((a) > (b) ? (a) : (b)) 

ssize_t readn(int fd, void *vptr, size_t n);

ssize_t writen(int fd, const void *vptr, size_t n);

static int read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];

static ssize_t my_read(int fd, char *ptr);

ssize_t readline(int fd, void *vptr, size_t maxlen);

ssize_t Readn(int fd, void *ptr, size_t nbytes);

void Writen(int fd, void *ptr, size_t nbytes);

ssize_t Readline(int fd, void *ptr, size_t maxlen);

ssize_t Read(int fd, void *ptr, size_t nbytes);

void Write(int fd, void *ptr, size_t nbytes);

int Open(const char *pathname, int flags, mode_t mode);

void Close(int fd);

void Fputs(const char *ptr, FILE *stream);

char* Fgets(char *ptr, int n, FILE *stream);

void Sendto(int fd, const void* ptr, size_t nbytes, int flags, const struct sockaddr* sa, socklen_t salen);

ssize_t Recvfrom(int fd, void* ptr, size_t nbytes, int flags, struct sockaddr* sa, socklen_t* salenptr);

pid_t Fork();
