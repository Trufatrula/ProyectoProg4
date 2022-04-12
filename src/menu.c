#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "datos.h"
#include "usuario.h"

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

void menuSesion() {
    char* opciones[] = {"Registrarse", "Iniciar sesión", "Sácame de aquí"};
    int o = opcion("¿Desea registarse o iniciar sesión? Indiquelo con los numeros correspondientes", 3, opciones);
	switch (o) {
	    case 0:
            
			break;
	    case 1:
            
			break;
        default:
            break;
	}
}

void menuPrincipal() {
    char* opciones[] = {"Ver usuario", "Añadir/Modificar/Borrar usuarios existentes", "Ver estadisticas", "Sácame de aquí"};
    int o;
    do {
        o = opcion("¿Deseas ver usuario, añadir/modificar/borrar usuarios existentes o ver estadisticas? Indiquelo con los numeros correspondientes", 4, opciones);
        switch (o) {
	        case 0:
                menuVerUsuario();
		    	break;
	        case 1:
                menuEdicionUsuariosAdmin();
		    	break;
            case 2:
                menuVerEstadistidasUsuario();
		    	break;
            default:
                break;
	    }
    } while(o != 3);
}
void menuVerUsuario()
{
    printf("\nBuscar al usuario por nickname: ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre,MAX_LINE);

    ////////////////////////////////////////////////////////////////////////
    //Falta funcion para sacar el usuario seleccionado de la base de datos//
    ////////////////////////////////////////////////////////////////////////
}

void menuEdicionUsuariosAdmin() {
    char* opciones[] = {"Añadir usuarios", "Modificar usuarios existentes", "Borrar usuarios", "Sácame de aquí"};
    int o;
    do {
        o = opcion("De todas esas opciones, ¿Deseas añadir, modificar o borrar el usuario? Indiquelo con los numeros correspondientes", 4, opciones);
	    switch (o) {
	        case 0:
                menuAnyadirUsuarios();
		    	break;
	        case 1:
                menuModificarUsuario();
		    	break;
            case 2:
                menuBorrarUsuario();
		    	break;
            default:
                break;
	    }
    } while(o != 3);
}

void menuAnyadirUsuarios() {
    printf("--------------------\nMETA LOS DATOS DEL USUARIO NUEVO\n--------------------\n");

    printf("Nombre: ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre,MAX_LINE);

    printf("\nApellido: ");
    char apellido[MAX_LINE];
    fgets(apellido, 20, stdin);
    clearIfNeeded(apellido,MAX_LINE);

    printf("\nNombre usuario: ");
    char nickname[MAX_LINE];
    fgets(nickname, 20, stdin);
    clearIfNeeded(nickname,MAX_LINE);

    printf("\nContraseña: ");
    char contrasenya[MAX_LINE];
    fgets(contrasenya, 20, stdin);
    clearIfNeeded(contrasenya,MAX_LINE);

    char* opciones[] = {"Usuario", "Administrador"};
    int o = opcion("¿Que tipo de usuario quieres que sea? Indiquelo con los numeros correspondientes", 2, opciones);

    Usuario usuario;
    iniciarUsuario(&usuario, nombre, apellido, nickname, contrasenya, o);
    registrarUsuario(&usuario);
    liberarUsuario(&usuario);
    
}
void menuModificarUsuario()
{
    printf("\nSeleccione el usuario que quieres modificar (nickname): ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre,MAX_LINE);
    Usuario usuario;
    if(obtenerDatosDeUsuario(&usuario, nombre) != 0)
    {
        printf("El nombre de usuario no existe");
    } else {
        printf("Nombre: %s\n", usuario.nombre);
        printf("Apellido: %s\n", usuario.apellido);
        printf("Nickname: %s\n", usuario.nickname);
        printf("Es admin: %i\n", usuario.admin);
        char* opciones[] = {"Nombre", "Apellido", "Nick", "Admin"};
        int o = opcion("¿Que valor quieres cambiar? Indiquelo con los numeros correspondientes", 4, opciones);
    
    }

}
void menuBorrarUsuario()
{
    printf("\nBorrar el usuario que quieres modificar (nickname): ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre,MAX_LINE);
}
void menuVerEstadistidasDeUsuario()
{
    printf("\nBorrar el usuario que quieres modificar (nickname): ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre,MAX_LINE);
    Usuario usuario;
    if(obtenerDatosDeUsuario(&usuario, nombre) != 0)
    {
        printf("El nombre de usuario no existe");
    } else {
        printf("Datos del usuario:\n");
        printf("Nombre: %s\n", usuario.nombre);
        printf("Apellido: %s\n", usuario.apellido);
        printf("Nickname: %s\n", usuario.nickname);
        printf("Es admin: %i\n", usuario.admin);
    }
}
void clearIfNeeded(char *str, int max_line) {
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
*/