#include "consola.h"
#include <stdio.h>

#ifdef _WIN32

void activarUTF8(){
    printf("Wind2us");
}
void desactivarUTF8(){
    printf("Desc");
}

#else

void activarUTF8(){
    printf("NO Wind2us");
}
void desactivarUTF8(){
    printf("NO Desc");
}

#endif