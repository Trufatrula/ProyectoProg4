#ifndef DATOS
#define DATOS

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#include "usuario.h"
#include "puntuaciones.h"

int registrarUsuario(Usuario* usuario);
int actualizarUsuario(Usuario* usuario);
int eliminarUsuario(char* nick);
int iniciarSesion(char* nick, char* contrasena, char* token, int expira);
int cerrarSesion(char* token);
int actualizarToken(char* token);
int obtenerNickDeToken(char* token, char* nick);
int obtenerDatosDeUsuario(Usuario* usuario, char* nick);
int usuarioExiste(char* nick);
int autorizar(char* token, char* nick);
int tokenExiste(char* token);
int obtenerPuntuaciones(Puntuaciones* puntuaciones, char* nick);
int generarTablas();
int abrirBD();
int cerrarBD();
int meterPalabraBD(char* palabra, char* tematica, char* idioma);

#ifdef __cplusplus
}
#endif

#endif