#include "datos.h"
#include <stdio.h>
#include <string.h>

int registrarUsuario(sqlite3 *db){

}

int inicioSesion(sqlite3 *db){

}

int generarTablas(sqlite3 *db){
    sqlite3_stmt *stmt;

	char sql[] = "CREATE TABLE IF NOT EXISTS Usuario( \
	Nombre TEXT NOT NULL,\
	Apellido TEXT,\
	Nick TEXT NOT NULL,\
	Contraseña TEXT,\
	Salt TEXT NOT NULL,\
	PRIMARY KEY(Nick))";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql)-1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

    printf("Sentencianinsertada satisfactoriamente\n");
    //free(stmt);
    free(sql);

    char sql[] = "CREATE TABLE Puntuacion (\
	User_Nick TEXT NOT NULL,\
	Normal_Score INTEGER NOT NULL,\
	League_Points INTEGER NOT NULL,\
	FOREIGN KEY(User_Nick) REFERENCES Usuario(Nick) ON DELETE CASCADE,\
	PRIMARY KEY(User_Nick))";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql)-1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

    printf("Sentencianinsertada satisfactoriamente\n");
    free(sql);

    char sql[] = "CREATE TABLE Diccionario (\
	Palabra	TEXT NOT NULL,\
	Tema TEXT NOT NULL,\
	Idioma	TEXT NOT NULL,\
	PRIMARY KEY(Palabra))";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql)-1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

    printf("Sentencianinsertada satisfactoriamente\n");
    free(sql);

    char sql[] = "CREATE TABLE Token (\
	User_Nick	TEXT NOT NULL,\
	Token	TEXT NOT NULL,\
	PRIMARY KEY(User_Nick))";

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

    sqlite3_finalize(stmt);
}

int abrirBD(sqlite3 *db){
    int result = sqlite3_open("WordleJALAD_BD.db", &db);
    if (result != SQLITE_OK) {
		printf("Error al abrir la base de datos\n");
		return result;
	}
}

int cerrarBD(sqlite3 *db){
    int result = sqlite3_close(db);
	if (result != SQLITE_OK) {
		printf("Error cerrando base de datos\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
}