#include "datos.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "token.h"

sqlite3* __baseDeDatosActual;

int registrarUsuario(Usuario* usuario) {
    //Aqui calculamos el salt y el token supongo
    sqlite3_stmt *stmt;
    char sqlUsuario[] = "INSERT INTO Usuario (Nombre, Apellido, Nick, Constrasenya, Salt, Admin) VALUES (?, ?, ?, ?, ?)";
    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuario, -1, &stmt, NULL) ;
    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
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
	return result;
}

int actualizarUsuario(Usuario* usuario) {
    sqlite3_stmt *stmt;
    char sqlUsuario[] = "UPDATE Usuario SET Nombre = ?, Apellido = ?, Constrasenya = ?, Salt = ?, Admin = ? WHERE Nick = ?";
    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuario, -1, &stmt, NULL) ;
    if (result != SQLITE_OK) {
		printf("Error preparing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    sqlite3_bind_text(stmt, 0, usuario->nombre, strlen(usuario->nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 1, usuario->apellido, strlen(usuario->apellido), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario->hash, strlen(usuario->hash), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario->salt, strlen(usuario->salt), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, usuario->admin);
    sqlite3_bind_text(stmt, 5, usuario->nickname, strlen(usuario->nickname), SQLITE_STATIC);
    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos\n");
		return result;
	}
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	return result;
}

int eliminarUsuario(char* nick) {
    sqlite3_stmt *stmt;
	char sqlEliminar[] = "DELETE FROM table	WHERE Nick = ?";
	int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlEliminar, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	sqlite3_bind_text(stmt, 0, nick, strlen(nick), SQLITE_STATIC);
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	return result;
}

int iniciarSesion(char* nick, char* contrasena, char* token) {
    sqlite3_stmt *stmt;
    char hashComputado[65];
    int login = 0;
    char sqlUsuario[] = "SELECT Constrasenya, Salt FROM Usuario WHERE Nick = ?";
    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuario, -1, &stmt, NULL) ;
    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    sqlite3_bind_text(stmt, 5, nick, strlen(nick), SQLITE_STATIC);
    do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            char* hash = (char*) sqlite3_column_text(stmt, 0);
            char* salt = (char*) sqlite3_column_text(stmt, 1);
            if (strlen(hash) == 64 && strlen(salt) == 32) {
                hashContrasena(contrasena, salt, hashComputado);
                if (strcmp(hash, hashComputado) == 0) login = 1;
            }
        }
    } while (result == SQLITE_ROW);
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    if (login == 1) {
        char sqlToken[] = "INSERT INTO Token (User_Nick, Token, Expira) VALUES {?, ?, ?)";
        time_t t;
        char token[33];
        time(&t);
        generateToken(token);
        t += 3600;
        
        int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlToken, -1, &stmt, NULL) ;
        if (result != SQLITE_OK) {
		    printf("Error preparing statement (INSERT)\n");
		    printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		    return result;
	    }
        sqlite3_bind_text(stmt, 0, nick, strlen(nick), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 1, token, strlen(token), SQLITE_STATIC);
        sqlite3_bind_int64(stmt, 2, t);

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
        return result;
    }
	return SQLITE_ERROR;
}

int obtenerNickDeToken(char* token) {
    return 0;
}

int obtenerDatosDeUsuario(Usuario* usuario, char* nick) {
    return 0;
}

int autorizar(char* token, char* nick) {
    return 0;
}

int generarTablas() {
    sqlite3_stmt *stmt;
	char sqlUsuarios[] = "CREATE TABLE IF NOT EXISTS Usuario( \
	Nombre TEXT NOT NULL,\
	Apellido TEXT,\
	Nick TEXT NOT NULL,\
	Contrasenya TEXT NOT NULL,\
	Salt TEXT NOT NULL,\
    Admin INTEGER NOT NULL,\
	PRIMARY KEY(Nick))";

    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuarios, -1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error creating table\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}

    char sqlPuntuacion[] = "CREATE TABLE Puntuacion (\
	User_Nick TEXT NOT NULL,\
	Normal_Score INTEGER NOT NULL,\
	League_Points INTEGER NOT NULL,\
	FOREIGN KEY(User_Nick) REFERENCES Usuario(Nick) ON DELETE CASCADE,\
	PRIMARY KEY(User_Nick))";

    result = sqlite3_prepare_v2(__baseDeDatosActual, sqlPuntuacion, -1, &stmt, NULL) ;  //No estoy seguro del parámetro 3 de la función, si debe ser strlen(sql), strlen(sql)+1, strlen(sql)-1

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }
    
    char sqlDiccionario[] = "CREATE TABLE Diccionario (\
	Palabra	TEXT NOT NULL,\
	Tema TEXT NOT NULL,\
	Idioma	TEXT NOT NULL,\
	PRIMARY KEY(Palabra))";

    result = sqlite3_prepare_v2(__baseDeDatosActual, sqlDiccionario, -1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error creating table\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}

    char sqlToken[] = "CREATE TABLE Token (\
	User_Nick	TEXT NOT NULL,\
	Token TEXT NOT NULL,\
    Expira INTEGER NOT NULL,\
	PRIMARY KEY(Token))";

    result = sqlite3_prepare_v2(__baseDeDatosActual, sqlToken, -1, &stmt, NULL) ;
    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }

    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error creating table\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    return SQLITE_OK;
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