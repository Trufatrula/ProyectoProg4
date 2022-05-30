#include "menu.h"
#include <iostream>
#include <string>
#include "../menu/menu.h"
#include "../sockets/tcom.h"
#include "../sockets/mensajes.h"
#include "sesion.h"
#include "conexion.h"

#define HOST "localhost"
#define PUERTO 6969

int menuInicio() {
    const char* opciones[] = {"Registro", "Inicio de Sesión", "Sacame de aquí"};
    int o;
    char msg[34], *r;
    unsigned long l;
    if (cargarToken("token.txt") == 0) {
        if (conectar(HOST, PUERTO) == 1) {
            return 1;
        }
        msg[0] = TOKENLOGIN;
        getToken(msg + 1);
        sendSizedMsg(socket_cliente, (unsigned char*) msg, 34);
        receiveSizedMsg(socket_cliente, (unsigned char**) &r, &l);
        if (l == 1 && r[0] == TOKENLOGIN) {
            free(r);
            return 0;
        }
        free(r);
    }


    do {
        o = opcion("Bienvenido, ¿quiere registrarse o iniciar sesión?", 3, opciones);
        switch (o)
        {
        case 0:
            if (menuRegistro() == 1) {
                return 1;
            }
            return 0;
        case 1:
            if (menuInicioSesion() == 1) {
                return 1;
            }
            return 0;
        default:
            break;
        }
    } while(o != 2);
}

int menuRegistro() {
    std::string nombre; 
    std::cout << "Nombre: "; 
    std::getline(std::cin, nombre);
    
    std::string apellido; 
    std::cout << "Apellido: "; 
    std::getline(std::cin, apellido);
    
    std::string nick; 
    std::cout << "Nick: "; 
    std::getline(std::cin, nick);

    std::string contrasena; 
    std::cout << "Contraseña: "; 
    std::getline(std::cin, contrasena);

    const char* opciones[] = {"No", "Si"};
    int o = opcion("¿Quieres que tu sesion expire al salir?", 2, opciones);
    return 0;
}

int menuInicioSesion() {
    std::string nick; 
    std::cout << "Nick: "; 
    std::getline(std::cin, nick);

    std::string contrasena; 
    std::cout << "Contraseña: "; 
    std::getline(std::cin, contrasena);

    const char* opciones[] = {"No", "Si"};
    int o = opcion("¿Quieres que tu sesion expire al salir?", 2, opciones);
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