#ifndef JALADSESION
#define JALADSESION

#include "../sockets/incluir.h"
#include <string.h>
#include <string>

class Sesion {
    private:
        char token[33];
        bool estado;
        std::string palabra;
        int intentos;
        SOCKET socket;


    public:

        Sesion(SOCKET socket);
        Sesion(const Sesion& s);

        bool recibir();

        bool iniciarSesionCliente(const char* usuario, const char* password, int expira);
        bool registerCliente(const char* usuario, const char* password, const char* nombre, const char* apellido, int expira);
        
        void nuevaPartida();
        void testPalabra(const std::string& palabra);

        inline void setToken(const char* token) {strcpy(this->token, token);}
        inline void setPalabra(const std::string& str) {this->palabra = str;}

        
       
        


};








#endif
