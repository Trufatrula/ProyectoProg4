#ifndef MENUS
#define MENUS

#define MAX_LINE 20

int opcion(char* mensaje, int cantidad, char** opciones);
int menuSesion();
void menuPrincipal();
void menuEdicionUsuariosAdmin();
int menuAnyadirUsuarios();
void menuModificarUsuario();
void menuBorrarUsuario();
int menuIniciarSesion();
//void menuVerEstadistidasUsuario();
//char mostrarMenuEstadisticas();
//char mostrarMenuCuenta(char* usuario);
void clearIfNeeded(char *str, int max_line);

#endif