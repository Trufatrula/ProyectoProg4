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
    unsigned char *buffer , *buffer2, *p;
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
            if(result){
                buffer2 = (unsigned char*) malloc(34);
                buffer2[0] = LOGIN;
                strcpy((char*) (buffer2 + 1), this->token);
                sendSizedMsg(this->socket, buffer2, 34);
                free(buffer2);
            } else {
                buffer2 = (unsigned char*) malloc(1);
                buffer2[0] = JALADERROR;
                sendSizedMsg(this->socket, buffer2, 1);
                free(buffer2);
            }
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
            free(buffer);
            return false;
        default:
            break;
    }
    free(buffer);
    return true;
    
    

}

bool Sesion::iniciarSesion(const char* usuario, const char* password, int expira){

}
        
void Sesion::nuevaPartida() {

}  
void Sesion::testPalabra(const std::string& palabra) {

}