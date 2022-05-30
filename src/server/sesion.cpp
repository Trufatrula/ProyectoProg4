#include "sesion.h"
#include "../sockets/tcom.h"
#include "../sockets/mensajes.h"


Sesion::Sesion(const Sesion& s) {
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


bool Sesion::recibir() {
    char* buffer;
}
        
void Sesion::nuevaPartida() {

}  
void Sesion::testPalabra(const std::string& palabra) {

}