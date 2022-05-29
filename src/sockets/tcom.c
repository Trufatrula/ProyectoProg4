#include "tcom.h"

void setupAddrStruct(char* str, struct in_addr* addr) {
    unsigned long rs = inet_addr(str);
    if (rs == INADDR_ANY || rs == INADDR_NONE) {
        printf("Resolving %s...\n", str);
        struct hostent* he = gethostbyname(str);
        if (he == NULL) {
            printf("Cannot resolve %s. Error 0x%x\n", str, WSAGetLastError());
            exit(5);
        }
        struct in_addr* ia = (struct in_addr*) he->h_addr_list[0];
        printf("Resolved %s as %s\n", str, inet_ntoa(*ia));
        memcpy(addr, ia, sizeof(unsigned long));
    } else {
        memcpy(addr, &rs, sizeof(unsigned long));
    }
}

void sendSizedMsg(SOCKET s, char* msg, unsigned long len) {
    unsigned long sent = 0;
    unsigned long slen;
    unsigned long nlen = htonl(len);
    int ret;
    if (send(s, &nlen, sizeof(unsigned long), 0) == SOCKET_ERROR) {
        printf("Cannot send the size of the data to be sent. Error: 0x%x\n", WSAGetLastError());
        exit(6);
    }
    while (sent < len) {
        slen = len - sent > TBUFF_SIZE ? TBUFF_SIZE : len - sent;
        ret = send(s, msg + sent, slen, 0);
        if (ret == SOCKET_ERROR) {
            printf("Cannot send the data. Error 0x%x", WSAGetLastError());
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
    if (recv(s, &size, sizeof(unsigned long), 0) == SOCKET_ERROR) {
        printf("Cannot fetch receiving data size. Error 0x%x", WSAGetLastError());
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
        ret = recv(s, mabuff + received, rlen, 0);
        if (ret == SOCKET_ERROR) {
            printf("Cannot receive the data. Error 0x%x", WSAGetLastError());
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
