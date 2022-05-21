#ifndef CONSOLA
#define CONSOLA

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32

#include <windows.h>

#endif

void activarUTF8();
void desactivarUTF8();

#ifdef __cplusplus
}
#endif

#endif