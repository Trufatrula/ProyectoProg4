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
    unsigned char *buffer , *p;
    char *usuario, *password;
    bool result;
    int expira;
    unsigned long l;
    if(receiveSizedMsg(this->socket, &buffer,&l) == 1) return false;
    switch (*buffer)
    {
        case LOGIN:
            p = buffer + 1;
            usuario = (char*) p;
            p += strlen(usuario)+1;
            password = (char*) p;
            p+= strlen(password)+1;
            expira = *p;
            result = this->iniciarSesion(usuario,password, expira);

            break;
        case REGISTER:

            break;
        case TOKENLOGIN:

            break;
        case PARTIDA:

            break;
        case PROBAR:

            break;
        case CLIENTESALIR:
        
            return false;
        default:
            break;
    }
    return true;
    
    

}

bool Sesion::iniciarSesion(const char* usuario, const char* password, int expira){

}
        
void Sesion::nuevaPartida() {

}  
void Sesion::testPalabra(const std::string& palabra) {

}