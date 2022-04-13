#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"
#include "datos.h"
#include "usuario.h"
#include "sesion.h"

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
            if (menuAnyadirUsuarios() == 0){
                printf("Iniciar sesión:\n");
                return menuIniciarSesion();
            } else {
                return 1;
            }
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

void menuPrincipal() {
    char* opciones[] = {"Ver y editar usuarios existentes", "Ver estadisticas", "Cerrar Sesion y salir", "Salir"};
    int o;
    do {
        o = opcion("¿Deseas ver usuario, añadir/modificar/borrar usuarios existentes o ver estadisticas? Indiquelo con los numeros correspondientes", 4, opciones);
        switch (o) {
	        case 0:
                menuEdicionUsuariosAdmin();
		    	break;
            case 1:
                //menuVerEstadistidasUsuario();
                printf("Aún no implementado\n");
		    	break;
            case 2:;
                char token[33];
                getToken(token);
                cerrarSesion(token);
                unlink("token.txt");
                break;
            default:
                break;
	    }
    } while(o != 2 && o != 3);
}

void menuEdicionUsuariosAdmin() {
    char* opciones[] = {"Añadir usuarios", "Ver/Modificar usuarios existentes", "Borrar usuarios", "Salir"};
    int o;
    do {
        o = opcion("De todas esas opciones, ¿Deseas añadir, ver/modificar o borrar el usuario? Indiquelo con los numeros correspondientes", 4, opciones);
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
            printf("Saliendo...");
                break;
	    }
    } while(o != 3);
}

int menuAnyadirUsuarios() {
    printf("--------------------\nMETA LOS DATOS DEL USUARIO NUEVO\n--------------------\n");

    printf("Nombre: ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre, MAX_LINE);

    printf("\nApellido: ");
    char apellido[MAX_LINE];
    fgets(apellido, 20, stdin);
    clearIfNeeded(apellido, MAX_LINE);

    printf("\nNombre usuario: ");
    char nickname[MAX_LINE];
    fgets(nickname, 20, stdin);
    clearIfNeeded(nickname, MAX_LINE);

    printf("\nContraseña: ");
    char contrasenya[MAX_LINE];
    fgets(contrasenya, 20, stdin);
    clearIfNeeded(contrasenya, MAX_LINE);

    char* opciones[] = {"Usuario", "Administrador"};
    int o = opcion("¿Que tipo de usuario quieres que sea? Indiquelo con los numeros correspondientes", 2, opciones);

    Usuario usuario;
    iniciarUsuario(&usuario, nombre, apellido, nickname, contrasenya, o);
    int resultado = registrarUsuario(&usuario);
    liberarUsuario(&usuario);
    if(resultado == 1){
        printf("No se ha podido registrar usuario\n");
        return 1;
    } else {
        printf("Se ha registrado el usuario\n");
        return 0;
    }
}

void menuModificarUsuario() {
    printf("\nSeleccione el usuario que quieres modificar (nickname): ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre, MAX_LINE);
    Usuario usuario;
    if(obtenerDatosDeUsuario(&usuario, nombre) != 0) {
        printf("El nombre de usuario no existe");
    } else {
        printf("Nombre: %s\n", usuario.nombre);
        printf("Apellido: %s\n", usuario.apellido);
        printf("Es admin: %i\n", usuario.admin);
        char* opciones[] = {"Nombre", "Apellido", "Admin", "Nada"};
        int o = opcion("¿Que valor quieres cambiar? Indiquelo con los numeros correspondientes", 4, opciones);
        switch (o) {
            case 0:
                printf("Introduce el nuevo nombre: ");
                char nombre[MAX_LINE];
                fgets(nombre, 20, stdin);
                clearIfNeeded(nombre, MAX_LINE);
                Usuario usuario0;
                crearUsuario(&usuario0, nombre, usuario.apellido, usuario.nickname, usuario.hash, usuario.salt, usuario.admin);
                actualizarUsuario(&usuario0);
                liberarUsuario(&usuario0);
                break;
            case 1:
                printf("Introduce el nuevo apellido: ");
                char apellido[MAX_LINE];
                fgets(apellido, 20, stdin);
                clearIfNeeded(apellido, MAX_LINE);
                Usuario usuario1;
                crearUsuario(&usuario1, usuario.nombre, apellido, usuario.nickname, usuario.hash, usuario.salt, usuario.admin);
                actualizarUsuario(&usuario1);
                liberarUsuario(&usuario1);
                break;
            case 2:
                printf("Introduce la nueva contraseña: ");
                char contrasenya[MAX_LINE];
                fgets(contrasenya, 20, stdin);
                clearIfNeeded(contrasenya, MAX_LINE);
                setContrasena(&usuario, contrasenya);
                actualizarUsuario(&usuario);
                break;
            case 3:
                printf("Introduce el nuevo valor de administrador: ");
                char* opcionesAdmin[] = {"Usuario", "Administrador"};
                int o2 = opcion("¿Que tipo de usuario quieres que sea? Indiquelo con los numeros correspondientes", 2, opcionesAdmin);
                Usuario usuario3;
                crearUsuario(&usuario3, nombre, usuario.apellido, usuario.nickname, usuario.hash, usuario.salt, o2);
                actualizarUsuario(&usuario3);
                liberarUsuario(&usuario3);
                break;
            default:
                break;
        }
        liberarUsuario(&usuario);
    }
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
            guardarToken("token.txt");
        }
        return 0;
    } else {
        printf("No se ha podido iniciar sesion, compruebe su usuario y contraseña");
        return 1;
    }
}


void menuBorrarUsuario() {
    printf("\nBorrar el usuario que quieres modificar (nickname): ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre, MAX_LINE);
    eliminarUsuario(nombre);
}

void menuVerEstadistidasDeUsuario() {
    printf("\nVer estadisticas del usuario (nickname): ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre, MAX_LINE);
    Usuario usuario;
    if(obtenerDatosDeUsuario(&usuario, nombre) != 0) {
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