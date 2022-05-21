#ifndef MENUS_COMMON
#define MENUS_COMMON

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LINE 20

int opcion(char* mensaje, int cantidad, char** opciones);
int menuAnyadirUsuarios();
void menuModificarUsuario();
void menuBorrarUsuario();
void clearIfNeeded(char *str, int max_line);

#ifdef __cplusplus
}
#endif

#endif