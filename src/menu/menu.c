#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"

#define MAX_LINE 20

int opcion(char* mensaje, int cantidad, char** opciones) {
    printf("%s:\n", mensaje);
    for (int i = 0; i < cantidad; i++) {
        printf(" %i. %s\n", i + 1, opciones[i]);
    }
    int opcion = 0;
    do {
        printf("Opción: (1 - %i): ", cantidad);
        char linea[MAX_LINE];
        fgets(linea, 20, stdin);
        sscanf(linea, "%i", &opcion);
    } while(opcion < 1 || opcion > cantidad);
    return opcion-1;
}

void clearIfNeeded(char *str, int max_line) {
    if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
}