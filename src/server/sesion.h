#ifndef JALADSESION
#define JALADSESION

#include "../sockets/incluir.h"

class Sesion {
    private:
        char token[16];
        bool estado;
        char* palabra;
        int intentos;
        SOCKET socket;


    public:

        Sesion(SOCKET socket);
        Sesion(const Sesion& s);
        ~Sesion();

        
        bool getEstado();
        void setEstado(bool estado);
        
        char* getPalabra();
        void setPalabra(char* palabra);
        
        int getIntentos();
        void setIntentos(int intentos);
        
        


};








#endif
