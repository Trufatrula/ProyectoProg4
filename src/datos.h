#ifndef DATOS
#define DATOS

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int registrarUsuario(sqlite3 *db);
int inicioSesion(sqlite3 *db);
int generarTablas(sqlite3 *db);

#endif