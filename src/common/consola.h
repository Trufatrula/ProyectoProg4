#ifndef CONSOLA
#define CONSOLA

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32

#include <windows.h>

#endif

void prepararConsola();
void restaurarConsola();

#ifdef __cplusplus
}
#endif

#endif