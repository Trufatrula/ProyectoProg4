#include "menu.h"
#include "sesion.h"
#include <stdio.h>

int menuSesion() {
    if(cargarToken("token.txt") == 0){
        char token[33];
        char nick[MAX_LINE];
        getToken(token);
        if(obtenerNickDeToken(token, nick) == 0){
            printf("Sesion automaticamente iniciada como %s\n", nick);
            return 0;
        }
    }
    char* opciones[] = {"Registrarse", "Iniciar sesión", "Sácame de aquí"};
    int o = opcion("¿Desea registarse o iniciar sesión? Indiquelo con los numeros correspondientes", 3, opciones);
	switch (o) {
	    case 0:

            /*
            if (menuAnyadirUsuarios() == 0){
                printf("Iniciar sesión:\n");
                return menuIniciarSesion();
            } else {
                return 1;
            }
            */
			break;
	    case 1:
            return menuIniciarSesion();
			break;
        default:
            printf("Saliendo...");
            return 1;
            break;
	}
    return 0;
}

int menuIniciarSesion() {
    char token[33];
    printf("\nNombre de usuario (nickname): ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre, MAX_LINE);
    printf("\nContraseña (nickname): ");
    char contrasenya[MAX_LINE];
    fgets(contrasenya, 20, stdin);
    clearIfNeeded(contrasenya, MAX_LINE);
    char* opcionCerrar[] = {"No", "Si"};
    int o = opcion("¿Quieres cerrar la sesion al salir? Indiquelo con los numeros correspondientes", 2, opcionCerrar);

    if(iniciarSesion(nombre, contrasenya, token, o) == 0){
        establecerToken(token);
        if(o == 0){
            //guardarToken("token.txt");
        }
        return 0;
    } else {
        printf("No se ha podido iniciar sesion, compruebe su usuario y contraseña");
        return 1;
    }
    */


   return 0;
}

int menuPrincipalJugador() {
    char* opciones[] = {"Jugar", "Mis datos", "Cerrar Sesión", "Salir"};
    int o;
    do {
        o = opcion("¿Que quieres hacer?", 4, opciones);
        switch (o) {
	        case 0:
                return menuJugar();
			    break;
	        case 1:
                //mostrarDatos();
                //Hay que hacerlo
			    break;
            case 2:
                //char token[33];
                //getToken(token);
                //cerrarSesion(token);
                //unlink("token.txt");
                break;  
            default:
                printf("Saliendo...");
                return 1;
                break;
	    }
        return 0;
    } while (o != 3 || o != 4);
}

int menuJugar() {
    char* opciones[] = {"Partida clásica", "Modo clasificatorio", "Modo épico", "Volver al menu principal"};
    int o = opcion("Selecciona el modo de juego", 4, opciones);
    switch (o) {
	    case 0:
            //jugarPartidaClasica();
			break;
	    case 1:
            //jugarPartidaClasificatoria();
			break;
        case 2:
            //jugarPartidaEpica();
            break;  
        default:
            printf("Volviendo...");
            return 1;
            break;
	}
    return 0;
}