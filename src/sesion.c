#include "sesion.h"
#include <string.h>
#include <stdio.h>

char __tokenactual[33];

void establecerToken(char* token){
    if(strlen(token) == 32){
        strcpy(__tokenactual, token);
    }
}

void getToken(char* token){
    strcpy(token, __tokenactual);
}

void guardarToken(char* nomFichero){
    FILE * fichero;
    fichero = fopen(nomFichero, "w");
    printf(__tokenactual);
    fputs(__tokenactual, fichero);
    fclose(fichero);
}

int cargarToken(char*nomFichero){
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