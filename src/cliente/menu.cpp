#include "menu.h"
#include <iostream>
#include <string>
#include <string.h>
#include "../menu/menu.h"
#include "../sockets/tcom.h"
#include "../sockets/mensajes.h"
#include "sesion.h"
#include "juego.h"
#include "conexion.h"

#define HOST "localhost"
#define PUERTO 6000

int menuInicio() {
    const char* opciones[] = {"Registro", "Inicio de Sesión", "Sacame de aquí"};
    int o;
    char msg[34], *r = 0;
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
    unsigned char* msg = (unsigned char*) malloc(len), *r = 0;
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
    if (r[0] != REGISTER) {
        free(r);
        return 1;
    }
    if (lenr != 34) {
        free(r);
        return 1;
    }
    establecerToken((char*) (r + 1));
    if (o == 1) guardarToken("token.txt");
    free(r);
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
    unsigned char* msg = (unsigned char*) malloc(len), *r = 0;
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
    if (r[0] != LOGIN) {
        free(r);
        return 1;
    }
    if (lenr != 34) {
        free(r);
        return 1;
    }
    establecerToken((char*) (r + 1));
    if (o == 1) guardarToken("token.txt");
    free(r);
    return 0;
}

int menuEditarNombreApellido() {
    std::string nombre; 
    std::cout << "Nuevo nombre: "; 
    std::getline(std::cin, nombre);
    
    std::string apellido; 
    std::cout << "Nuevo apellido: "; 
    std::getline(std::cin, apellido);

    size_t len = 3 + nombre.size() + apellido.size();
    unsigned long lenr;
    unsigned char* msg = (unsigned char*) malloc(len), *r = 0;
    char* p;
    msg[0] = UPDATEUSER;
    p = (char*) (msg + 1);
    strcpy(p, nombre.c_str());
    p +=  nombre.size() + 1;
    strcpy(p, apellido.c_str());
    sendSizedMsg(socket_cliente, msg, len);
    receiveSizedMsg(socket_cliente, &r, &lenr);
    if (r[0] != UPDATEUSER) {
        free(r);
        return 1;
    }
    if (lenr != 1) {
        free(r);
        return 1;
    }
    free(r);
    return 0;
}

int menuEditarContrasena() {
    std::string pass; 
    std::cout << "Nueva contraseña: "; 
    std::getline(std::cin, pass);

    size_t len = 2 + pass.size();
    unsigned long lenr;
    unsigned char* msg = (unsigned char*) malloc(len), *r = 0;
    char* p;
    msg[0] = UPDATEPASS;
    p = (char*) (msg + 1);
    strcpy(p, pass.c_str());
    sendSizedMsg(socket_cliente, msg, len);
    receiveSizedMsg(socket_cliente, &r, &lenr);
    if (r[0] != UPDATEPASS) {
        free(r);
        return 1;
    }
    if (lenr != 1) {
        free(r);
        return 1;
    }
    free(r);
    return 0;
}

int menuCliente() {
    unsigned char msg[1], *r = 0;
    unsigned long l;
    int puntos;
    const char* opciones[] = {"Jugar", "Ver puntuaciones", "Editar usuario", "Cerrar sesión", "Sácame de aquí"};
    int o;
    do {
        o = opcion("Bienvenido, ¿Qué quiere hacer hoy?", 5, opciones);
        switch (o)
        {
        case 0:
            if (menuJuego() == 1) {
                return 1;
            }
            break;
        case 1:
            msg[0] = INFOPUNTOS;
            sendSizedMsg(socket_cliente, msg, 1);
            receiveSizedMsg(socket_cliente, &r, &l);
            if (r[0] == INFOPUNTOS) {
                memcpy(&puntos, r + 1, sizeof(int));
                std::cout << "Tienes " << puntos << " puntos." << std::endl;
            } else {
                std::cout << "No se ha podido obtener tu puntuación" << std::endl;
            }
            free(r);
            break;
        case 2: 
            if (menuEditarCliente() == 2) {
                return 0;
            }
        case 3: //cerra sesion
            break;
        default:
            return 0;
            break;
        }
    } while(o != 3);
    return 0;
}

int menuEditarCliente() {
    unsigned char msg[1], *r = 0;
    unsigned long l;
    const char* opciones[] = {"Borrar usuario", "Editar usuario", "Editar constraseña", "Me arrepiento..."};
    int o;
    do {
        o = opcion("¿De qué forma quieres editar tu usuario?", 4, opciones);
        switch (o)
        {
        case 0:
            msg[0] = USERDEL;
            sendSizedMsg(socket_cliente, msg, 1);
            receiveSizedMsg(socket_cliente, &r, &l);
            if (r[0] == USERDEL) {
                std::cout << "Usuario borrado. Saliendo..." << std::endl;
                free(r);
                return 2;
            } else {
                free(r);
                std::cout << "No se ha podido borrar el usuario" << std::endl;
            }
            break;
        case 1:
            if (menuEditarNombreApellido() == 1) {
                std::cout << "No se han podido editar los datos del usuario" << std::endl;
            } else {
                std::cout << "Se han editado los datos del usuario" << std::endl;
            }
            break;
        case 2:
             if (menuEditarContrasena() == 1) {
                std::cout << "No se ha podido editar la contraseña" << std::endl;
            } else {
                std::cout << "Se ha editado la contraseña" << std::endl;
            }
            break;
        case 3:
            //adios
            break;
        default:
            return 0;
            break;
        }
    } while(o != 3);
    return 0;
}

int menuJuego() {
    Partida partida;
    if (partida.iniciar() == 1) return 1;

    return 0;
}