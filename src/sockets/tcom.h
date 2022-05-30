#pragma once
#ifndef INCLUDE_TCON_H
#define INCLUDE_TCON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "incluir.h"

#define TBUFF_SIZE 1024

void setupAddrStruct(char* str, struct in_addr* addr);
int sendSizedMsg(SOCKET s, const unsigned char* msg, unsigned long len);
int receiveSizedMsg(SOCKET s, unsigned char** mabuff, unsigned long* ptrlen);

#ifdef __cplusplus
}
#endif

#endif // INCLUDE_TCON_H
