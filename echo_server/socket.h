#include "common.h"

#define SA struct sockaddr

int Socket(int family, int type, int protocol);

void Connect(int fd, const struct sockaddr *sa, socklen_t salen);

void Listen(int fd, int backlog);

void Bind(int fd, const struct sockaddr *sa, socklen_t salen);

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Inet_pton(int family, const char *strptr, void *addrptr);

const char* Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);

