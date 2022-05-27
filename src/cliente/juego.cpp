#include "juego.h"
#include "string.h"
#include <iostream>
#include <cstring>
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

char* Partida::getPalabra() {
    return this->palabra;
}

Partida::Partida(const char* palabra) {
    this->palabra = new char[strlen(palabra)+1];
    strcpy(this->palabra, palabra);
}

Partida::Partida(const Partida& p) {
    this->palabra = new char[strlen(p.palabra)+1];
    strcpy(this->palabra, p.palabra);

    this->puntuacion=p.puntuacion;
    this->intentos=p.intentos;
    this->ganada=p.ganada;
}

Partida::~Partida() {
    delete[] this->palabra;
}

int Partida::comprobarResultado(char* palabraUser, char* codigoServer) {
    for (int i = 0; i < strlen(codigoServer); i++)
    {   
        char asa = palabraUser[i];
        if(codigoServer[i]=='*') {
            cout<<GRN <<palabraUser[i]<<NC;
        } else if (codigoServer[i]=='-'){
            cout<<RED <<palabraUser[i]<<NC;
        } else if (codigoServer[i]=='/'){
            cout<<NC <<palabraUser[i]<<NC;
        }
        
    }
    

}
