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
int eliminarUsuario(const char* nick);
int iniciarSesion(const char* nick, const char* contrasena, char* token, int expira);
int cerrarSesion(const char* token);
int actualizarToken(const char* token);
int obtenerNickDeToken(const char* token, char* nick);
int obtenerDatosDeUsuario(Usuario* usuario, const char* nick);
int usuarioExiste(const char* nick);
int autorizar(const char* token, const char* nick);
int tokenExiste(const char* token);
int obtenerPuntuaciones(Puntuaciones* puntuaciones, const char* nick);
int borrarPalabras();
int generarTablas();
int abrirBD();
int cerrarBD();
int meterPalabraBD(char* palabra, char* tematica, char* idioma);
int existePalabra(char* palabra);
int getPalabraRandom(char* palabra, char* categoria, char* idioma);

#ifdef __cplusplus
}
#endif

#endif