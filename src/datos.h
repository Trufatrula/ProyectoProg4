#ifndef DATOS
#define DATOS

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#include "usuario.h"

int registrarUsuario(Usuario* usuario);
int actualizarUsuario(Usuario* usuario);
int eliminarUsuario(char* nick);
int iniciarSesion(char* nick, char* contrasena, char* token, int expira);
int cerrarSesion(char* token);
int actualizarToken(char* token);
int obtenerNickDeToken(char* token, char* nick);
int obtenerDatosDeUsuario(Usuario* usuario, char* nick);
int autorizar(char* token, char* nick);
int tokenExiste(char* token);
int generarTablas();
int abrirBD();
int cerrarBD();

#endif