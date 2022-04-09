#ifndef MENUS
#define MENUS

char mostrarMenu();
char mostarMenuUsuario();
char mostrarMenuJugar();
char mostrarMenuEstadisticas();
char mostrarMenuCuenta(char* usuario);
void registro();
void inicioSesion();
void clearIfNeeded(char *str, int max_line);

#endif