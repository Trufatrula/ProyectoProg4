#ifndef UTILIDADES
#define UTILIDADES

#ifdef __cplusplus
extern "C" {
#endif

void hexABin(const char* entrada, unsigned int size, unsigned char* salida);
void binAHex(const unsigned char* entrada, unsigned int size, char* salida);


#ifdef __cplusplus
}
#endif

#endif