#ifndef JALADJUEGO
#define JALADJUEGO

class Partida {
    private:
        int puntuacion;
        int intentos;
        unsigned long size;
        int ganada;

    public:
        Partida();
        Partida(const Partida& p);
        ~Partida();
        int getPuntuacion();
        int getIntentos();
        int getGanada();
        void setPuntuacion(int puntuacion);
        void setIntentos(int intentos);
        void setGanada(int ganada);
        void comprobarResultado(const char* palabraUser, const char* codigoServer);
        int iniciar(); //Te prntea la categoria longitud intentos
        int testPalabra();
};

#endif