#ifndef PUNTUACIONES_H_
#define PUNTUACIONES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int Normal_Score;

} Puntuaciones;

void crearPuntuacion(Puntuaciones* puntuacion, int normal);

#ifdef __cplusplus
}
#endif

#endif