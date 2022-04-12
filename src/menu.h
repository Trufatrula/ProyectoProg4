#ifndef MENUS
#define MENUS

int opcion(char* mensaje, int cantidad, char** opciones);
void menuSesion();
void menuPrincipal();
void menuVerUsuario();
void menuEdicionUsuariosAdmin();
void menuAnyadirUsuarios();
void menuModificarUsuario();
void menuBorrarUsuario();
void menuVerEstadistidasUsuario();
//char mostrarMenuEstadisticas();
//char mostrarMenuCuenta(char* usuario);
void clearIfNeeded(char *str, int max_line);

#endif