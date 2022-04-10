#include "datos.h"
#include <stdio.h>
#include <string.h>

int registrarUsuario(sqlite3 *db, char* Nombre, char* Apellido, char* Nick, char* Contrasenya){
    //Aqui calculamos el salt y el token supongo
    sqlite3_stmt *stmt;
    char sql[] = "INSERT INTO Usuario (Nombre, Apellido, Nick, Constrasenya, Salt) values (?, ?, ?, ?, ?)";
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (INSERT)\n");

    sqlite3_bind_text(stmt, 0, Nombre, strlen(Nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 1, Apellido, strlen(Apellido), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, Nick, strlen(Nick), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, Contrasenya, strlen(Contrasenya), SQLITE_STATIC);
    //sqlite3_bind_text(stmt, 4, Salt, strlen(Salt), SQLITE_STATIC);     //Cuando sepa como carallo se calcula lo metemos lol

    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos\n");
		return result;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Statement finalizado (INSERT)\n");

	return SQLITE_OK;
    
}

int inicioSesion(sqlite3 *db){

}

int generarTablas(sqlite3 *db){
    sqlite3_stmt *stmt;

	char sql[] = "CREATE TABLE IF NOT EXISTS Usuario( \
	Nombre TEXT NOT NULL,\
	Apellido TEXT,\
	Nick TEXT NOT NULL,\
	Contrasenya TEXT,\
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

    int result = sqlite3_prepare_v2(db, sql, strlen(sql)-1, &stmt, NULL) ;  //No estoy seguro del parámetro 3 de la función, si debe ser strlen(sql), strlen(sql)+1, strlen(sql)-1

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