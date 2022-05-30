#ifndef SESION
#define SESION

#ifdef __cplusplus
extern "C" {
#endif

void establecerToken(const char* token);
void getToken(char* token);
void guardarToken(const char* fichero);
int cargarToken(const char* fichero);

#ifdef __cplusplus
}
#endif

#endif