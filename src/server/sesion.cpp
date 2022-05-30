#include "sesion.h"


Sesion::Sesion(const Sesion& s) {
    if(s.palabra != NULL) {
        this->palabra = new char[strlen(s.palabra)+1];
        strcpy(this->palabra, s.palabra);
    }
    
    this->setToken(s.token);
    this->estado=s.estado;
    this->intentos=s.intentos;
    this->socket = s.socket;    
}

Sesion::Sesion(SOCKET s) {
    this->socket = s;
    this->estado = false;
    this->intentos = 0;
    memset(this->token, 0, 16);
}


Sesion::~Sesion() {
    if (this->palabra != NULL) delete[] this->palabra;
}