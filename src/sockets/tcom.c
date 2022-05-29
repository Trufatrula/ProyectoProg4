#include "tcom.h"
#include <string.h>
#include <stdlib.h>

#ifdef __WIN32
typedef char* socketsend_t;
#else
typedef void* socketsend_t;
#endif

void setupAddrStruct(char* str, struct in_addr* addr) {
    unsigned long rs = inet_addr(str);
    if (rs == INADDR_ANY || rs == INADDR_NONE) {
        printf("Resolving %s...\n", str);
        struct hostent* he = gethostbyname(str);
        if (he == NULL) {
            printf("Cannot resolve %s.\n", str);
            exit(5);
        }
        struct in_addr* ia = (struct in_addr*) he->h_addr_list[0];
        printf("Resolved %s as %s\n", str, inet_ntoa(*ia));
        memcpy(addr, ia, sizeof(unsigned long));
    } else {
        memcpy(addr, &rs, sizeof(unsigned long));
    }
}

void sendSizedMsg(SOCKET s, const char* msg, unsigned long len) {
    unsigned long sent = 0;
    unsigned long slen;
    unsigned long nlen = htonl(len);
    int ret;
    if (send(s, (const socketsend_t*) &nlen, sizeof(unsigned long), 0) == SOCKET_ERROR) {
        printf("Cannot send the size of the data to be sent.\n");
        exit(6);
    }
    while (sent < len) {
        slen = len - sent > TBUFF_SIZE ? TBUFF_SIZE : len - sent;
        ret = send(s, (const socketsend_t*) (msg + sent), slen, 0);
        if (ret == SOCKET_ERROR) {
            printf("Cannot send the data.\n");
            exit(6);
        }
        if (ret > 0) {
            sent += ret;
        } else {
            break;
        }
    }
}

char* receiveSizedMsg(SOCKET s, char* mabuff, unsigned long* ptrlen) {
    unsigned long size;
    unsigned long received = 0;
    unsigned long rlen;
    int ret;
    if (recv(s, (socketsend_t*) &size, sizeof(unsigned long), 0) == SOCKET_ERROR) {
        printf("Cannot fetch receiving data size.\n");
        exit(6);
    }
    size = ntohl(size);
    if (ptrlen != NULL) {
        *ptrlen = size;
    }
    mabuff = realloc(mabuff, ((size_t) size) + 1);
    memset(mabuff, 0, ((size_t) size) + 1);
    if (mabuff == 0) {
        printf("Cannot reallocate the memory to hold the reply.\n");
        exit(10);
    }
    while (received < size) {
        rlen = size - received > TBUFF_SIZE ? TBUFF_SIZE : size - received;
        ret = recv(s, (socketsend_t*) (mabuff + received), rlen, 0);
        if (ret == SOCKET_ERROR) {
            printf("Cannot receive the data.\n");
            exit(6);
        }
        if (ret > 0) {
            received += ret;
        } else {
            break;
        }
    }
    return mabuff;
}
