#include "consola.h"
#include <stdio.h>

#ifdef _WIN32

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

UINT CPANTIGUO;
DWORD MODOANTIGUO;

void prepararConsola() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CPANTIGUO = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
    GetConsoleMode(h, &MODOANTIGUO);
    SetConsoleMode(h, MODOANTIGUO | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
void restaurarConsola() {
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