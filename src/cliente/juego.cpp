#include "juego.h"
#include "string.h"
#include <iostream>
#include <cstring>
#include "../sockets/mensajes.h"
#include "../sockets/tcom.h"
#include "conexion.h"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define NC "\e[0m"

using namespace std;

int Partida::getPuntuacion() {
    return this->puntuacion;
}

int Partida::getIntentos() {
    return this->intentos;
}

void Partida::setPuntuacion(int puntuacion) {
    this->puntuacion=puntuacion;

}

void Partida::setIntentos(int intentos) {
    this->intentos=intentos;
}

void Partida::setGanada(int ganada) {
    if(ganada==0 && ganada==1){
        this->ganada=ganada;
    }
}



Partida::Partida() {
    /*this->palabra = new char[strlen(palabra)+1];
    strcpy(this->palabra, palabra);*/
}

Partida::Partida(const Partida& p) {
    /*this->palabra = new char[strlen(p.palabra)+1];
    strcpy(this->palabra, p.palabra);*/

    this->puntuacion=p.puntuacion;
    this->intentos=p.intentos;
    this->ganada=p.ganada;
}

Partida::~Partida() {

}

void Partida::comprobarResultado(const char* palabraUser, const char* codigoServer) {
    for (size_t i = 0; i < strlen(codigoServer); i++)
    {   
        if(codigoServer[i]=='*') {
            cout<<GRN <<palabraUser[i]<<NC;
        } else if (codigoServer[i]=='-'){
            cout<<RED <<palabraUser[i]<<NC;
        } else if (codigoServer[i]=='/'){
            cout<<NC <<palabraUser[i]<<NC;
        }
        
    }
    cout << NC;

}

int Partida::iniciar() {
    unsigned char msg[1], *r = 0;
    char *p, *categoria, *idioma;
    unsigned long l;
    msg[0] = PARTIDA;
    sendSizedMsg(socket_cliente, msg, 1);
    receiveSizedMsg(socket_cliente, &r, &l);
    if (r[0] != PARTIDA) {
        std::cerr << "No se ha inicado la partida" << std::endl;
        free(r);
        return 1;
    }
    p = (char*) (r + 1);
    categoria = p;
    p += strlen(categoria) + 1;
    idioma = p;
    p += strlen(idioma) + 1;
    memcpy(&this->intentos, p, sizeof(size_t));
    free(r);
    std::cout << "Has iniciado una partida. La temática de la palabra es " << categoria << ", el idioma es " << idioma << " y la longitud es de " << this->intentos << " por lo que tienes " << this->intentos << " intentos." << endl;
    return 0;
}

int Partida::testPalabra() {
    std::string palabra;
    std::cout << "Introduce tu palabra" << endl;
    std::getline(std::cin, palabra);
    return 0;
    //Servidor hace cosas////
    //comprobarResultado(palabra, cosa del server);       Necesitamos lo del server
}
