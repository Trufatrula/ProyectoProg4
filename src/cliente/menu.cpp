#include "menu.h"
#include <iostream>
#include <string>
#include <string.h>
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
        desconectar();
        if (l == 1 && r[0] == TOKENLOGIN) {
            free(r);
            return 0;
        }
        free(r);
    }

    conectar(HOST, PUERTO);
    do {
        o = opcion("Bienvenido, ¿quiere registrarse o iniciar sesión?", 3, opciones);
        switch (o)
        {
        case 0:
            if (menuRegistro() == 1) {
                std::cerr << "Ha ocurrido un error al registrar el usuario" << std::endl;
                desconectar();
                return 1;
            }
            return 0;
        case 1:
            if (menuInicioSesion() == 1) {
                std::cerr << "El usuario o la contraseña es incorrecta" << std::endl;
                desconectar();
                return 1;
            }
            return 0;
        default:
            break;
        }
    } while(o != 2);
    return 1;
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

    size_t len = 5 + nombre.size() + apellido.size() + nick.size() + contrasena.size() + sizeof(char);
    unsigned long lenr;
    unsigned char* msg = (unsigned char*) malloc(len), *r;
    char* p;
    msg[0] = REGISTER;
    p = (char*) (msg + 1);
    strcpy(p, nick.c_str());
    p +=  nick.size() + 1;
    strcpy(p, contrasena.c_str());
    p += contrasena.size() + 1;
    strcpy(p, nombre.c_str());
    p += nombre.size() + 1;
    strcpy(p, apellido.c_str());
    p += apellido.size() + 1;
    *p = (char) o;
    sendSizedMsg(socket_cliente, msg, len);
    receiveSizedMsg(socket_cliente, &r, &lenr);
    if (r[0] != REGISTER) return 1;
    if (lenr != 34) return 1;
    establecerToken((char*) (r + 1));
    if (o == 1) guardarToken("token.txt");
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

    size_t len = 3 + nick.size() + contrasena.size() + sizeof(char);
    unsigned long lenr;
    unsigned char* msg = (unsigned char*) malloc(len), *r;
    char* p;
    msg[0] = LOGIN;
    p = (char*) (msg + 1);
    strcpy(p, nick.c_str());
    p +=  nick.size() + 1;
    strcpy(p, contrasena.c_str());
    p += contrasena.size() + 1;
    *p = (char) o;
    sendSizedMsg(socket_cliente, msg, len);
    receiveSizedMsg(socket_cliente, &r, &lenr);
    if (r[0] != LOGIN) return 1;
    if (lenr != 34) return 1;
    establecerToken((char*) (r + 1));
    if (o == 1) guardarToken("token.txt");

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

int menuEditarCliente() {
    const char* opciones[] = {"Borrar usuario", "Editar usuario", "Editar constraseña", "Me arrepiento..."};
    int o;
    do {
        o = opcion("¿De qué forma quieres editar tu usuario?", 4, opciones);
        switch (o)
        {
        case 0:
            //Server borra
            break;
        case 1:
            //Server edita
            break;
        case 2:
            //Server edita contraseña
            break;
        case 3:
            //adios
            break;
        default:
            return 0;
            break;
        }
    } while(o != 4);
    return 0;
}

int menuJuego() {
    return 0;
}