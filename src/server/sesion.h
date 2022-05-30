#ifndef JALADSESION
#define JALADSESION

#include "../sockets/incluir.h"
#include <memory.h>
#include <string>

class Sesion {
    private:
        unsigned char token[16];
        bool estado;
        std::string palabra;
        int intentos;
        SOCKET socket;


    public:

        Sesion(SOCKET socket);
        Sesion(const Sesion& s);
        ~Sesion();

        inline void setToken(const unsigned char* token) {memcpy(this->token, token,16);}
        inline void setPalabra(const std::string& str) {this->palabra = str;}

        
       
        


};








#endif
