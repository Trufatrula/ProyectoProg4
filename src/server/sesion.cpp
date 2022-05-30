#include "sesion.h"
#include "../sockets/tcom.h"
#include "../sockets/mensajes.h"
#include "../datos/datos.h"
#include "../datos/usuario.h"
#include "../datos/puntuaciones.h"
#include <mutex>

std::mutex clientMutex;

Sesion::Sesion(const Sesion& s) {
    this->setToken(s.token);
    this->intentos=s.intentos;
    this->socket = s.socket;
    this->logeado = s.logeado;
}

Sesion::Sesion(SOCKET s) {
    this->socket = s;
    this->logeado = false;
    this->intentos = 0;
    memset(this->token, 0, 16);
}


bool Sesion::recibir() {
    std::lock_guard<std::mutex> lock(clientMutex);
    unsigned char *buffer , *buffer2, *p;
    char *usuario, *password, *nombre, *apellido, *token;
    bool result;
    int expira;
    Usuario u, u2;
    Puntuaciones punt;
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
                this->logeado = true;
                buffer2[0] = TOKENLOGIN;
            }else{
                buffer2[0] = JALADERROR;
            }
            free(buffer2);
            break;
        case PARTIDA:
            if (this->logeado && this->intentos == 0) {
                this->nuevaPartida((char**) &buffer2);
            } else {
                buffer2 = (unsigned char*) malloc(1);
                buffer2[0] = JALADERROR;
                sendSizedMsg(this->socket, buffer2, 1);
            }
            free(buffer2);
            break;
        case PROBAR:
            if (this->logeado && this->intentos-- > 0) {
                this->testPalabra((char*) (buffer + 1), (char**) &buffer2);
            } else {
                buffer2 = (unsigned char*) malloc(1);
                buffer2[0] = JALADERROR;
                sendSizedMsg(this->socket, buffer2, 1);
            }
            free(buffer2);
            break;
        case INFOUSER:
            if (this->logeado) {
                usuario = (char*) malloc(20);
                if (obtenerNickDeToken(this->token, usuario) != SQLITE_OK) {
                    buffer2 = (unsigned char*) malloc(1);
                    buffer2[0] = JALADERROR;
                    sendSizedMsg(this->socket, buffer2, 1);
                } else {
                    if (obtenerDatosDeUsuario(&u, usuario) == SQLITE_OK) {
                        buffer2 = (unsigned char*) malloc(1 + strlen(u.nombre) + strlen(u.apellido) + 2);
                        buffer2[0] = INFOUSER;
                        p = buffer2 + 1;
                        strcpy((char*) p, u.nombre);
                        p += strlen(u.nombre) + 1;
                        strcpy((char*) p, u.apellido);
                        sendSizedMsg(this->socket, buffer2, 1 + strlen(u.nombre) + strlen(u.apellido) + 2);
                        liberarUsuario(&u);
                    } else {
                        buffer2 = (unsigned char*) malloc(1);
                        buffer2[0] = JALADERROR;
                        sendSizedMsg(this->socket, buffer2, 1);
                    }
                }
                free(usuario);
            } else {
                buffer2 = (unsigned char*) malloc(1);
                buffer2[0] = JALADERROR;
                sendSizedMsg(this->socket, buffer2, 1);
            }
            free(buffer2);
            break;
        case UPDATEUSER:
            buffer2 = (unsigned char*) malloc(1);
            if (this->logeado) {
                usuario = (char*) malloc(20);
                if (obtenerNickDeToken(this->token, usuario) != SQLITE_OK) {
                    buffer2[0] = JALADERROR;
                } else {
                    if (obtenerDatosDeUsuario(&u, usuario) == SQLITE_OK) {
                        p = buffer + 1;
                        nombre = (char*) p;
                        p += strlen(nombre) + 1;
                        apellido = (char*) p;
                        crearUsuario(&u2, nombre, apellido, u.nickname, u.hash, u.salt);
                        if (actualizarUsuario(&u2) != SQLITE_OK) {
                            buffer2[0] = JALADERROR;
                        } else {
                            buffer2[0] = UPDATEUSER;
                        }
                        liberarUsuario(&u);
                        liberarUsuario(&u2);
                    } else {
                        buffer2[0] = JALADERROR;
                    }
                }
                free(usuario);
            } else {
                buffer2[0] = JALADERROR;
            }
            sendSizedMsg(this->socket, buffer2, 1);
            free(buffer2);
            break;
        case UPDATEPASS:
            buffer2 = (unsigned char*) malloc(1);
            if (this->logeado) {
                usuario = (char*) malloc(20);
                if (obtenerNickDeToken(this->token, usuario) != SQLITE_OK) {
                    buffer2[0] = JALADERROR;
                } else {
                    if (obtenerDatosDeUsuario(&u, usuario) == SQLITE_OK) {
                        p = buffer + 1;
                        password = (char*) p;
                        setContrasena(&u, password);
                        if (actualizarUsuario(&u) != SQLITE_OK) {
                            buffer2[0] = JALADERROR;
                        } else {
                            buffer2[0] = UPDATEPASS;
                        }
                        liberarUsuario(&u);
                        liberarUsuario(&u2);
                    } else {
                        buffer2[0] = JALADERROR;
                    }
                }
                free(usuario);
            } else {
                buffer2[0] = JALADERROR;
            }
            sendSizedMsg(this->socket, buffer2, 1);
            free(buffer2);
            break;
        case USERDEL:
            buffer2 = (unsigned char*) malloc(1);
            if (this->logeado) {
                usuario = (char*) malloc(20);
                if (obtenerNickDeToken(this->token, usuario) != SQLITE_OK) {
                    buffer2[0] = JALADERROR;
                } else {
                    buffer2[0] = USERDEL;
                    eliminarUsuario(usuario);
                }
                free(usuario);
            } else {
                buffer2[0] = JALADERROR;
            }
            sendSizedMsg(this->socket, buffer2, 1);
            free(buffer2);
            free(buffer);
            return false;
        case INFOPUNTOS:
            if (this->logeado) {
                usuario = (char*) malloc(20);
                if (obtenerNickDeToken(this->token, usuario) != SQLITE_OK) {
                    buffer2 = (unsigned char*) malloc(1);
                    buffer2[0] = JALADERROR;
                    sendSizedMsg(this->socket, buffer2, 1);
                } else {
                    if (obtenerPuntuaciones(&punt, usuario) != SQLITE_OK) {
                        buffer2 = (unsigned char*) malloc(1 + sizeof(int));
                        buffer2[0] = INFOPUNTOS;
                        memcpy(buffer2 + 1, &punt.Normal_Score, sizeof(int));
                        sendSizedMsg(this->socket, buffer2, 1 + sizeof(int));
                        free(buffer2);
                    } else {
                        buffer2 = (unsigned char*) malloc(1);
                        buffer2[0] = JALADERROR;
                        sendSizedMsg(this->socket, buffer2, 1);
                    }
                }
                free(usuario);
            } else {
                buffer2 = (unsigned char*) malloc(1);
                buffer2[0] = JALADERROR;
                sendSizedMsg(this->socket, buffer2, 1);
            }
            free(buffer2);
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
    liberarUsuario(&u);
    if(r != SQLITE_OK) return false;
    this->logeado = true;
    return this->iniciarSesionCliente(usuario, password, expira);
}

bool Sesion::iniciarSesionCliente(const char* usuario, const char* password, int expira){
    int r = iniciarSesion(usuario, password, this->token, expira);
    if( r == SQLITE_OK) {
        this->logeado = true;
    }
    return false;
}
        
void Sesion::nuevaPartida(char** buffer) {
    char palabra[100];
    char categoria[100];
    char idioma[20];
    getPalabraRandom(palabra, categoria, idioma);
    unsigned long l = strlen(palabra) + strlen(categoria) + strlen(idioma) + sizeof(size_t) + 4;
    this->palabra = std::string(palabra);
    *buffer = (char*) malloc(l);
    char* p = *buffer;
    *p = PARTIDA;
    p++;
    strcpy(p, palabra);
    p += strlen(palabra) + 1;
    strcpy(p, categoria);
    p += strlen(categoria) + 1;
    strcpy(p, idioma);
    p += strlen(idioma) + 1;
    size_t* s = (size_t*) p;
    *s = strlen(palabra);
    this->intentos = strlen(palabra);
    sendSizedMsg(this->socket, (unsigned char*) *buffer, l);
}  

void Sesion::testPalabra(char* p, char** buffer) {
    bool win = true;
    if (strlen(p) != this->palabra.size()) {
        *buffer = (char*) malloc(2);
        *buffer[0] = PARTIDA;
        *buffer[1] = PARTIDA_ERROR;
        sendSizedMsg(this->socket, (unsigned char*) *buffer, 2);
    } else {
        bool found = false;
        *buffer = (char*) malloc(2 + strlen(p) + 1);
        *buffer[0] = PARTIDA;
        *buffer[1] = PARTIDA_OK;
        char* p = *buffer + 2;
        for (std::size_t i = 0; i < this->palabra.size(); i++, p++) {
            found = false;
            if (tolower(this->palabra[i]) == tolower(p[i])) {
                *p = '*';
                continue;
            }
            win = false;
            for (std::size_t j = 0; j < this->palabra.size(); j++) {
                if (tolower(p[i]) == tolower(this->palabra[j])) {
                    *p = '/';
                    found = true;
                    break;
                }
            }
            if (found) continue;
            *p = '-';
        }
        *p = 0;
        if (win) {
            char nick[20];
            Puntuaciones punt;
            if (obtenerNickDeToken(this->token, nick) != SQLITE_OK) {
                *buffer[0] = JALADERROR;
                sendSizedMsg(this->socket, (unsigned char*) *buffer, 1);
                return;
            } else {
                if (obtenerPuntuaciones(&punt, nick) != SQLITE_OK) {
                    punt.Normal_Score += this->intentos + 1;
                    
                } else {
                    *buffer[0] = JALADERROR;
                    sendSizedMsg(this->socket, (unsigned char*) *buffer, 1);
                    return;
                }
            }
        }
        sendSizedMsg(this->socket, (unsigned char*) *buffer, 2 + strlen(p) + 1);
    }
}