#include "consola.h"
#include <stdio.h>

#ifdef _WIN32

UINT CPANTIGUO;

void activarUTF8() {
    CPANTIGUO = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
}
void desactivarUTF8() {
    SetConsoleOutputCP(CPANTIGUO);
}

#else

void activarUTF8() {

}
void desactivarUTF8() {

}

#endif