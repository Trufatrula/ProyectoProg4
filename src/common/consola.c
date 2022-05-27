#include "consola.h"
#include <stdio.h>

#ifdef _WIN32

UINT CPANTIGUO;
DWORD MODOANTIGUO;

void prepararConsola() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CPANTIGUO = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
    GetConsoleMode(h, &MODOANTIGUO);
    SetConsoleMode(h, MODOANTIGUO | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
void desactivarUTF8() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CPANTIGUO);
    SetConsoleMode(h, MODOANTIGUO);
}

#else

void prepararConsola() {

}
void restaurarConsola() {

}

#endif