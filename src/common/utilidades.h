#ifndef UTILIDADES
#define UTILIDADES

#ifdef __cplusplus
extern "C" {
#endif

void hexABin(char* entrada, unsigned int size, unsigned char* salida);
void binAHex(unsigned char* entrada, unsigned int size, char* salida);

#ifdef __cplusplus
}
#endif

#endif