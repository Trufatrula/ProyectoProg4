#include "menu.h"
#include <iostream>
#include <string>
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
            return 0;
            break;
        }
    } while(o != 2);
}

int menuRegistro() {
    std::string nombre; 
    std::cout << "Nombre: "; 
    std::cin >> nombre;
    
    std::string apellido; 
    std::cout << "Apellido: "; 
    std::cin >> apellido;
    
    std::string nick; 
    std::cout << "Nick: "; 
    std::cin >> nick;

    std::string contrasena; 
    std::cout << "Contraseña: "; 
    std::cin >> contrasena;

    const char* opciones[] = {"No", "Si"};
    int o = opcion("¿Quieres que tu sesion expire al salir?", 2, opciones);

    std::cout << nombre << apellido << nick << contrasena << o << std::endl;

    return 0;
}

int menuInicioSesion() {
    return 0;
}

int menuCliente() {
    const char* opciones[] = {"Jugar", "Ver puntuaciones", "Cerrar sesión", "Sácame de aquí"};
    int o;
    do {
        o = opcion("Bienvenido, ¿Qué quiere hacer hoy?", 4, opciones);
        switch (o)
        {
        case 0:
            if (menuJuego() == 1) {
                return 1;
            }
            break;
        case 1:
            //verPuntuaciones
            break;
        case 2:

            break;
        default:
            return 0;
            break;
        }
    } while(o != 3);
    return 0;
}

int menuJuego() {
    return 0;
}