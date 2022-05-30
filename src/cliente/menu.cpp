#include "menu.h"
#include <iostream>
#include "../menu/menu.h"

int menuInicio() {
    const char* opciones[] = {"Registro", "Inicio de Sesión", "Sacame de aquí"};
    int o;
    do {
        o = opcion("Bienvenido, ¿quiere registrarse o iniciar sesión?", 3, opciones);
        switch (o)
        {
        case 0:
            if (menuRegistro() == 1) {
                return 1;
            }
            break;
        case 1:
            if (menuInicioSesion() == 1) {
                return 1;
            }
            break;
        default:
            break;
        }
    } while(o != 2);
    return 0;
}

int menuRegistro() {
    return 0;
}

int menuInicioSesion() {
    return 0;
}

int menuCliente() {
    return 0;
}

int menuJuego() {
    return 0;
}