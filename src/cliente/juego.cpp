#include "juego.h"
#include "string.h"
#include <iostream>

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

int Partida::iniciarPartida() {


}
