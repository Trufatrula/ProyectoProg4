#include "sesion.h"
#include <string.h>
#include <stdio.h>

char __tokenactual[33];

void establecerToken(const char* token){
    if(strlen(token) == 32){
        strcpy(__tokenactual, token);
    }
}

void getToken(char* token){
    strcpy(token, __tokenactual);
}

void guardarToken(const char* nomFichero){
    FILE * fichero;
    fichero = fopen(nomFichero, "w");
    fputs(__tokenactual, fichero);
    fclose(fichero);
}

int cargarToken(const char*nomFichero){
    FILE * fichero;
    fichero = fopen(nomFichero, "r");
    if(fichero == NULL){
        return 1;
    }
    fread(__tokenactual, 32, 1, fichero);
    __tokenactual[32] = 0;
    fclose(fichero);
    return 0;
}