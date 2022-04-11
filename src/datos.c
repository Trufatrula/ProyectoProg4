#include "datos.h"
#include <stdio.h>
#include <string.h>

sqlite3* __baseDeDatosActual;

int registrarUsuario(Usuario* usuario) {
    //Aqui calculamos el salt y el token supongo
    sqlite3_stmt *stmt;
    char sqlUsuario[] = "INSERT INTO Usuario (Nombre, Apellido, Nick, Constrasenya, Salt, Admin) values (?, ?, ?, ?, ?)";
    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuario, strlen(sqlUsuario) + 1, &stmt, NULL) ;
    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	printf("SQL query prepared (INSERT)\n");
    sqlite3_bind_text(stmt, 0, usuario->nombre, strlen(usuario->nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 1, usuario->apellido, strlen(usuario->apellido), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario->nickname, strlen(usuario->nickname), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario->hash, strlen(usuario->hash), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, usuario->salt, strlen(usuario->salt), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, usuario->admin);
    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos\n");
		return result;
	}
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	printf("Statement finalizado (INSERT)\n");
	return result;
}



int inicioSesion() {
    
    return 0;
}

int generarTablas() {
    sqlite3_stmt *stmt;

	char sqlUsuarios[] = "CREATE TABLE IF NOT EXISTS Usuario( \
	Nombre TEXT NOT NULL,\
	Apellido TEXT,\
	Nick TEXT NOT NULL,\
	Contrasenya TEXT,\
	Salt TEXT NOT NULL,\
    Admin INT NOT NULL,\
	PRIMARY KEY(Nick))";

    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuarios, strlen(sqlUsuarios)-1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

    char sqlPuntuacion[] = "CREATE TABLE Puntuacion (\
	User_Nick TEXT NOT NULL,\
	Normal_Score INTEGER NOT NULL,\
	League_Points INTEGER NOT NULL,\
	FOREIGN KEY(User_Nick) REFERENCES Usuario(Nick) ON DELETE CASCADE,\
	PRIMARY KEY(User_Nick))";

    result = sqlite3_prepare_v2(__baseDeDatosActual, sqlPuntuacion, strlen(sqlPuntuacion)-1, &stmt, NULL) ;  //No estoy seguro del parámetro 3 de la función, si debe ser strlen(sql), strlen(sql)+1, strlen(sql)-1

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }


    char sqlDiccionario[] = "CREATE TABLE Diccionario (\
	Palabra	TEXT NOT NULL,\
	Tema TEXT NOT NULL,\
	Idioma	TEXT NOT NULL,\
	PRIMARY KEY(Palabra))";

    result = sqlite3_prepare_v2(__baseDeDatosActual, sqlDiccionario, strlen(sqlDiccionario)-1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

    /*
    char sqlToken[] = "CREATE TABLE Token (\
	User_Nick	TEXT NOT NULL,\
	Token	TEXT NOT NULL,\
	PRIMARY KEY(Token))";

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

    sqlite3_finalize(stmt);
    */

    return result;
}

int abrirBD(sqlite3 *db) {
    int result = sqlite3_open("WordleJALAD_BD.db", &__baseDeDatosActual);
    if (result != SQLITE_OK) {
		printf("Error al abrir la base de datos\n");
		return result;
	}
    return result;
}

int cerrarBD(sqlite3 *db) {
    int result = sqlite3_close(__baseDeDatosActual);
	if (result != SQLITE_OK) {
		printf("Error cerrando base de datos\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    __baseDeDatosActual = 0;
    return result;
}