#ifndef MENUS
#define MENUS

int opcion(char* mensaje, int cantidad, char** opciones);
void menuSesion();
void menuPrincipal();
void menuEdicionUsuariosAdmin();
char mostrarMenuJugar();
char mostrarMenuEstadisticas();
char mostrarMenuCuenta(char* usuario);
void clearIfNeeded(char *str, int max_line);

#endif