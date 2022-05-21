#ifndef PUNTUACIONES_H_
#define PUNTUACIONES_H_

typedef struct {
    int Normal_Score;
    int League_Points;

} Puntuaciones;

void crearPuntuacion(Puntuaciones* puntuacion, int normal, int LP);

#endif