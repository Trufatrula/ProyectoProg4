#include "sesion.h"




bool Sesion::getEstado() {
    return this->estado;
}

void Sesion::setEstado(bool estado) {
    this->estado = estado;

}

char* Sesion::getPalabra() {
    return this->palabra;
}

void Sesion::setPalabra(char* palabra) {
    this->palabra = palabra;
}

int Sesion::getIntentos() {
return this->intentos;
}

void Sesion::setIntentos(int intentos) {
    this->intentos = intentos;
}


Sesion::Sesion(const Sesion& s) {

    //this->token = new char[strlen(s.token)+1];
    for (int i = 0; i < strlen(s.token)+1; i++)
    {
      //  strcpy(this->token,s.token[i]);
    }
    
    this->estado=s.estado;
    this->palabra=s.palabra;
    this->intentos=s.intentos;


}


Sesion::~Sesion() {

    delete[] this->token;
    delete[] this->palabra;
}