#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    return opcion;
}

void menuSesion(){
    char* opciones[] = {"Registrarse", "Iniciar sesión", "Sácame de aquí"};
    int o = opcion("Desea registarse o iniciar sesión? Indiquelo con los numeros correspondientes", 3, opciones);
	switch (o){
	    case 0:
            
			break;
	    case 1:
            
			break;
        default:
            break;
	}
}

void clearIfNeeded(char *str, int max_line){
    if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
}




/*

char mostrarMenuJugar()
{
    printf("-----------------------------------\n¿Que modo de juego quieres jugar? Escriba el numero correspondiente\n-----------------------------------\n");
    printf("1. Reto Diario\n");
    printf("2. WordleJALAD por numero de letras\n");
    printf("3. WordleJALAD por tematica\n");
    printf("4. Reto Contrareloj\n");
    printf("5. WordleJALAD : Multijugador\n");
    printf("6. Volver\n");
    printf("-> \n");
    fflush(stdout);
    char opcion[MAX_LINE];
    fgets(opcion, MAX_LINE, stdin);

    return *opcion;

}

char mostrarMenuEstadisticas()
{
    printf("-----------------------------------\n¿Que estadisticas quieres consultar? Escriba el numero correspondiente\n-----------------------------------\n");
    printf("1. Horas jugadas\n");
    printf("2. Puntuacion total : Reto Diario\n");
    printf("3. Puntuacion total : WordleJALAD por numero de letras\n");
    printf("4. Puntuacion total : WordleJALAD por tematica\n");
    printf("5. Puntuacion total : Reto Contrareloj\n");
    printf("6. Puntuacion total : WordleJALAD : Multijugador\n");
    printf("Pulsa 'q' para volver\n");
    printf("-> \n");
    fflush(stdout);
    char opcion[MAX_LINE];
    fgets(opcion, MAX_LINE, stdin);

    return *opcion;

}
*/
char mostrarMenuCuenta(char* usuario)
{
    printf("-CUENTA DE %s -\n",usuario);
    printf("1. Cambiar nombre usuario\n");
    printf("2. Cambiar contraseña del usuario\n");
    printf("3. Borrar cuenta\n");
    printf("4. Para ºvolver\n");
    printf("-> \n");
    fflush(stdout);
    char opcion[MAX_LINE];
    fgets(opcion, MAX_LINE, stdin);

    return *opcion;

}
