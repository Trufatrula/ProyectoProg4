#ifndef INCLUIRSOCKET
#define INCLUIRSOCKET

#ifdef __WIN32
typedef int socklen_t;
#include <winsock2.h>
#else
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SOCKET_ERROR -1
typedef int SOCKET;
#define closesocket close
#define SD_BOTH SHUT_RDWR
#endif

#endif