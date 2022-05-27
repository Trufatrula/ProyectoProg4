#include "utilidades.h"

void hexABin(char* entrada, unsigned int size, unsigned char* salida) {
    unsigned int binLen = size / 2;
    for (unsigned int i = 0, j = 0; i < binLen; i++, j += 2) {
        char c = entrada[j], c2 = entrada[j + 1];
        unsigned char n, n2;
        if (c >= '0' && c <= '9') {
            n = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            n = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            n = c - 'A' + 10;
        } else {
            n = 0;
        }
        if (c2 >= '0' && c2 <= '9') {
            n2 = c2 - '0';
        } else if (c2 >= 'a' && c2 <= 'f') {
            n2 = c2 - 'a' + 10;
        } else if (c2 >= 'A' && c2 <= 'F') {
            n2 = c2 - 'A' + 10;
        } else {
            n2 = 0;
        }
        salida[i] = (n << 4) | n2;
    }
}

void binAHex(unsigned char* entrada, unsigned int size, char* salida) {
    unsigned long hexLen = size * 2;
    for (unsigned int i = 0, j = 0; i < hexLen; i+=2, j++) {
        unsigned char n = entrada[j] >> 4, n2 = entrada[j] & 0x0f;
        char c, c2;
        if (n < 0xa) {
            c = n + '0';
        } else if (n < 0x10) {
            c = n + 'a' - 10;
        } else {
            c = '0';
        }
        if (n2 < 0xa) {
            c2 = n2 + '0';
        } else if (n < 0x10) {
            c2 = n2 + 'a' - 10;
        } else {
            c2 = '0';
        }
        salida[i] = c;
        salida[i + 1] = c2;
    }
    salida[hexLen] = 0;
}

void establecerColor(int color) {
    printf("\n%i", color);
}