#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../datos/datos.h"
#include "../datos/usuario.h"
#include "../datos/token.h"

void menuPrincipalAdmin() {
    char* opciones[] = {"Ver y editar usuarios existentes", "Ver estadisticas", "Salir"};
    int o;
    do {
        o = opcion("¿Deseas ver usuario, añadir/modificar/borrar usuarios existentes o ver estadisticas? Indiquelo con los numeros correspondientes", 3, opciones);
        switch (o) {
	        case 0:
                menuEdicionUsuariosAdmin();
		    	break;
            case 1:
                //menuVerEstadistidasUsuario();
                printf("Aún no implementado\n");
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
                menuAnyadirUsuariosAdmin();
		    	break;
	        case 1:
                menuModificarUsuarioAdmin();
		    	break;
            case 2:
                menuBorrarUsuarioAdmin();
		    	break;
            default:
            printf("Saliendo...\n");
                break;
	    }
    } while(o != 3);
}

int menuAnyadirUsuariosAdmin() {
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

void menuModificarUsuarioAdmin() {
    printf("\nSeleccione el usuario que quieres modificar (nickname): ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre, MAX_LINE);
    Usuario usuario;
    if(obtenerDatosDeUsuario(&usuario, nombre) != 0) {
        printf("El nombre de usuario no existe\n");
    } else {
        printf("Nombre: %s\n", usuario.nombre);
        printf("Apellido: %s\n", usuario.apellido);
        printf("Es admin: %i\n", usuario.admin);
        char* opciones[] = {"Nombre", "Apellido", "Contraseña", "Admin", "Nada"};
        int o = opcion("¿Que valor quieres cambiar? Indiquelo con los numeros correspondientes", 5, opciones);
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

void menuBorrarUsuarioAdmin() {
    printf("\nBorrar el usuario que quieres modificar (nickname): ");
    char nombre[MAX_LINE];
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre, MAX_LINE);
    eliminarUsuario(nombre);
}