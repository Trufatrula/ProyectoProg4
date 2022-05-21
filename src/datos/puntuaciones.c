#include "puntuaciones.h"
#include <stdlib.h>

void crearPuntuacion(Puntuaciones* puntuacion, int normal, int LP) {
    puntuacion->Normal_Score = normal;
    puntuacion->League_Points = LP;

}