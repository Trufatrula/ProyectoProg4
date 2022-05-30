#ifndef PUNTUACIONES_H_
#define PUNTUACIONES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int Normal_Score;
    int League_Points;

} Puntuaciones;

void crearPuntuacion(Puntuaciones* puntuacion, int normal, int LP);

#ifdef __cplusplus
}
#endif

#endif