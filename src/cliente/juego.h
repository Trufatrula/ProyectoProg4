#ifndef JALADJUEGO
#define JALADJUEGO

class Partida {
    private:
        int puntuacion;
        int intentos;
        int ganada;
        char* palabra;

    public:
        Partida(const char* palabra);
        Partida(const Partida& p);
        ~Partida();
        int getPuntuacion();
        int getIntentos();
        int getGanada();
        void setPuntuacion(int puntuacion);
        void setIntentos(int intentos);
        void setGanada(int ganada);
        char* getPalabra();
        void comprobarResultado(const char* palabraUser, const char* codigoServer);
};

#endif