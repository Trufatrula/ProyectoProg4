#ifndef MENUS_ADMIN
#define MENUS_ADMIN

#ifdef __cplusplus
extern "C" {
#endif

#include "../menu/menu.h"

void menuPrincipalAdmin();
void menuEdicionUsuariosAdmin();
int menuAnyadirUsuariosAdmin();
void menuModificarUsuarioAdmin();
void menuBorrarUsuarioAdmin();
void menuVerPuntuacionesAdmin();
void menuCargarPalabrasAdmin();
int menuSeleccionCargado();

#ifdef __cplusplus
}
#endif

#endif