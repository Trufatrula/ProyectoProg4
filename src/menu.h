#ifndef MENUS
#define MENUS

int opcion(char* mensaje, int cantidad, char** opciones);
void menuSesion();
char mostrarMenuJugar();
char mostrarMenuEstadisticas();
char mostrarMenuCuenta(char* usuario);
void registro();
void inicioSesion();
void clearIfNeeded(char *str, int max_line);

#endif