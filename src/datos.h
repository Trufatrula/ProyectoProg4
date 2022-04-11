#ifndef DATOS
#define DATOS

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#include "usuario.h"

int registrarUsuario(Usuario* usuario);
int inicioSesion();
int generarTablas();
int abrirBD();
int cerrarBD();

#endif