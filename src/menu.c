#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define MAX_LINE 20

char mostrarMenu(){

}
char mostarMenuUsuario(){
    printf("¿Desea registarse o iniciar sesión? Indíquelo con los números correspondientes\n");
	printf("1. Registrarse\n");
	printf("2. Iniciar Sesión\n");
	printf("3. Sácame de aquí\n");
	printf("\n");
	printf("Opción: ");
	fflush(stdout);
	char linea[MAX_LINE];
	fgets(linea, MAX_LINE, stdin);
	clearIfNeeded(linea, MAX_LINE);
	return *linea;
}
void registro(){

}
void inicioSesion(){

}
void clearIfNeeded(char *str, int max_line){
    if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
}