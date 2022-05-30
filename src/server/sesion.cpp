#include "sesion.h"
#include "../sockets/tcom.h"
#include "../sockets/mensajes.h"
#include "../datos/datos.h"
#include "../datos/usuario.h"


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
    char *usuario, *password, *nombre, *apellido, *token;
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
            result = this->iniciarSesionCliente(usuario,password, expira);
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
            p = buffer + 1;
            usuario = (char*) p;
            p += strlen(usuario) + 1;
            password = (char*) p;
            p += strlen(password) + 1;
            nombre = (char*) p;
            p += strlen(nombre) + 1;
            apellido = (char*) p;
            p += strlen(apellido) + 1;
            expira = *p;
            result = this->registerCliente(usuario, password, nombre, apellido, expira);
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
        case TOKENLOGIN:
            p = buffer +1;
            token = (char*) p;
            buffer2 = (unsigned char*) malloc(1);
            if(actualizarToken(token) == SQLITE_OK){
                strcpy(this->token, token);
                buffer2[0] = TOKENLOGIN;
            }else{
                buffer2[0] = JALADERROR;
            }
            free(buffer2);
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

bool Sesion::registerCliente(const char* usuario, const char* password, const char* nombre, const char* apellido, int expira){
    Usuario u;
    iniciarUsuario(&u, nombre, apellido,usuario, password);
    int r = registrarUsuario(&u);
    if(r != SQLITE_OK) return false;
    return this->iniciarSesionCliente(usuario, password, expira);
}

bool Sesion::iniciarSesionCliente(const char* usuario, const char* password, int expira){
    int r = iniciarSesion(usuario, password, this->token, expira);
    if( r == SQLITE_OK) return true;
    return false;
}
        
void Sesion::nuevaPartida() {

}  
void Sesion::testPalabra(const std::string& palabra) {

}