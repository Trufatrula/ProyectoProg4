#include "datos.h"
#include <stdio.h>
#include <string.h>
#include <openssl/rand.h>
#include <time.h>
#include "token.h"

#define MAX_STR_SIZE 20
#define TOKEN_TIME 3600

sqlite3* __baseDeDatosActual;

int registrarUsuario(Usuario* usuario) {
	if (usuarioExiste(usuario->nickname)) return SQLITE_ERROR;
    sqlite3_stmt *stmt;
    char sqlUsuario[] = "INSERT INTO Usuario (Nombre, Apellido, Nick, Contrasenya, Salt) VALUES (?, ?, ?, ?, ?)";
    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuario, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    sqlite3_bind_text(stmt, 1, usuario->nombre, strlen(usuario->nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario->apellido, strlen(usuario->apellido), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario->nickname, strlen(usuario->nickname), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, usuario->hash, strlen(usuario->hash), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, usuario->salt, strlen(usuario->salt), SQLITE_STATIC);
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

	char sqlUserPoints[] = "INSERT INTO Puntuacion (User_Nick, Normal_Score, League_Points) VALUES (?, 0, 0)";
	result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUserPoints, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	sqlite3_bind_text(stmt, 1, usuario->nickname, strlen(usuario->nickname), SQLITE_STATIC);
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
    char sqlUsuario[] = "UPDATE Usuario SET Nombre = ?, Apellido = ?, Contrasenya = ?, Salt = ? WHERE Nick = ?";
    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuario, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    sqlite3_bind_text(stmt, 1, usuario->nombre, strlen(usuario->nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario->apellido, strlen(usuario->apellido), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario->hash, strlen(usuario->hash), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, usuario->salt, strlen(usuario->salt), SQLITE_STATIC);

    sqlite3_bind_text(stmt, 6, usuario->nickname, strlen(usuario->nickname), SQLITE_STATIC);
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

int eliminarUsuario(const char* nick) {
    sqlite3_stmt *stmt;
	char sqlEliminar[] = "DELETE FROM Usuario WHERE Nick = ?";
	int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlEliminar, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	sqlite3_bind_text(stmt, 1, nick, strlen(nick), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error borrando datos\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	char sqlEliminarToken[] = "DELETE FROM Token WHERE User_Nick = ?";
	result = sqlite3_prepare_v2(__baseDeDatosActual, sqlEliminarToken, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	sqlite3_bind_text(stmt, 1, nick, strlen(nick), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error borrando datos\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	char sqlEliminarPuntuacion[] = "DELETE FROM Puntuacion WHERE User_Nick = ?";
	result = sqlite3_prepare_v2(__baseDeDatosActual, sqlEliminarPuntuacion, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	sqlite3_bind_text(stmt, 1, nick, strlen(nick), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error borrando datos\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	return result;
}

int iniciarSesion(const char* nick, const char* contrasena, char* token, int expira) {
    sqlite3_stmt *stmt;
    char hashComputado[65];
    int login = 0;
    char sqlUsuario[] = "SELECT Contrasenya, Salt FROM Usuario WHERE Nick = ?";
    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuario, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    sqlite3_bind_text(stmt, 1, nick, strlen(nick), SQLITE_STATIC);
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
        char sqlToken[] = "INSERT INTO Token (User_Nick, Token, Expira) VALUES (?, ?, ?)";
        time_t t;
        char to[33];
		if (expira) {
			time(&t);
		} else {
			t = 0x6fffffffffffffff;
		}
		do {
			generateToken(to);
		} while (tokenExiste(to));
        t += TOKEN_TIME;
        int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlToken, -1, &stmt, NULL);
        if (result != SQLITE_OK) {
		    printf("Error preparing statement (INSERT)\n");
		    printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		    return result;
	    }
        sqlite3_bind_text(stmt, 1, nick, strlen(nick), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, to, strlen(to), SQLITE_STATIC);
        sqlite3_bind_int64(stmt, 3, t);

        result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) {
		    printf("Error insertando datos\n");
			printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		    return result;
	    }
		strcpy(token, to);
        result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) {
		    printf("Error finalizando statement (INSERT)\n");
		    printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		    return result;
	    }
        return SQLITE_OK;
    }
	return SQLITE_ERROR;
}

int cerrarSesion(const char* token) {
	sqlite3_stmt *stmt;
	char sqlToken[] = "DELETE FROM Token WHERE Token = ?";
	int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlToken, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	sqlite3_bind_text(stmt, 1, token, strlen(token), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error borrando datos\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	return result;
}

int actualizarToken(const char* token) {
	sqlite3_stmt *stmt;
	time_t t;
	time(&t);
    char sqlTokenDel[] = "DELETE FROM Token WHERE Expira < ?";
    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlTokenDel, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    sqlite3_bind_int64(stmt, 1, t);
    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error eliminando datos\n");
		return result;
	}
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	t += TOKEN_TIME;
	char sqlTokenUpd[] = "UPDATE Token SET Expira = ? WHERE Expira < ? AND token = ?";
    result = sqlite3_prepare_v2(__baseDeDatosActual, sqlTokenUpd, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    sqlite3_bind_int64(stmt, 1, t);
	sqlite3_bind_int64(stmt, 2, t);
	sqlite3_bind_text(stmt, 3, token, strlen(token), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error eliminando datos\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	return result;
}

int obtenerNickDeToken(const char* token, char* nick) {
	 sqlite3_stmt *stmt;
	 int correcto = 0;
	 char sqlUsuario[] = "SELECT User_Nick FROM Token WHERE Token = ?";
	 actualizarToken(token);
	 int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuario, -1, &stmt, NULL);
	 if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }
	sqlite3_bind_text(stmt, 1, token, strlen(token), SQLITE_STATIC);
	do {
		result = sqlite3_step(stmt);
		if(result == SQLITE_ROW) {
			char* nicko = (char*) sqlite3_column_text(stmt,0);
			if(strlen(nicko) < MAX_STR_SIZE) {
				strcpy(nick,nicko);
				correcto = 1;
			}
		}
	}while (result == SQLITE_ROW);
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	if (correcto == 1) {
		return SQLITE_OK;
	}
	return SQLITE_ERROR;
}

int obtenerDatosDeUsuario(Usuario* usuario, const char* nick) {
	 sqlite3_stmt *stmt;
	 int correcto = 0;
	 char sqlUsuario[] = "SELECT * FROM Usuario WHERE Nick =?";
	 int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuario, -1, &stmt, NULL);
	 if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }
	sqlite3_bind_text(stmt, 1, nick, strlen(nick), SQLITE_STATIC);
	do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            char* hash = (char*) sqlite3_column_text(stmt, 3);
            char* salt = (char*) sqlite3_column_text(stmt, 4);
            if (strlen(hash) == 64 && strlen(salt) == 32) {
				char* nombre = (char*) sqlite3_column_text(stmt,0);
				char* apellido = (char*) sqlite3_column_text(stmt,1);
				char* nicko = (char*) sqlite3_column_text(stmt,2);
				correcto = 1;
				crearUsuario(usuario,nombre,apellido,nicko,hash,salt);
			}
        }
    } while (result == SQLITE_ROW);
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	if (correcto == 1) {
		return SQLITE_OK;
	}
	return SQLITE_ERROR;
}

int usuarioExiste(const char* nick) {
	sqlite3_stmt *stmt;
	 int correcto = 0;
	 char sqlNick[] = "SELECT Nick FROM Usuario WHERE Nick = ?";
	 int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlNick, -1, &stmt, NULL);
	 if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }
	sqlite3_bind_text(stmt, 1, nick, strlen(nick), SQLITE_STATIC);
	do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
        	correcto = 1;
        }
    } while (result == SQLITE_ROW);
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	if (correcto) return SQLITE_ERROR;
	return SQLITE_OK;
}

int autorizar(const char* token, const char* nick) {
	char nicktoken[MAX_STR_SIZE];
	if(obtenerNickDeToken(token, nicktoken) != SQLITE_OK) {
		return SQLITE_ERROR;
	}
	if (nick != NULL) {
		if(strcmp(nick, nicktoken) == 0) {
			return SQLITE_OK;
		}		
	}
	Usuario usuario;
	if(obtenerDatosDeUsuario(&usuario, nicktoken) != SQLITE_OK) {
		return SQLITE_ERROR;
	}
	liberarUsuario(&usuario);
	return SQLITE_ERROR;		
}

int tokenExiste(const char* token) {
	sqlite3_stmt *stmt;
	 int correcto = 0;
	 char sqlToken[] = "SELECT Token FROM Token WHERE Token = ?";
	 int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlToken, -1, &stmt, NULL);
	 if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }
	sqlite3_bind_text(stmt, 1, token, strlen(token), SQLITE_STATIC);
	do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            correcto = 1;
        }
    } while (result == SQLITE_ROW);
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	if (correcto == 1) return SQLITE_ERROR;
	return SQLITE_OK;
}

int obtenerPuntuaciones(Puntuaciones* puntuaciones, const char* nick) {
	 sqlite3_stmt *stmt;
	 int correcto = 0;
	 char sqlPuntuaciones[] = "SELECT Normal_Score, League_Points FROM Puntuacion WHERE User_Nick =?";
	 int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlPuntuaciones, -1, &stmt, NULL);
	 if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }
	sqlite3_bind_text(stmt, 1, nick, strlen(nick), SQLITE_STATIC);
	do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            
			int normal = (int) sqlite3_column_int(stmt,1);
			int LP = (int) sqlite3_column_int(stmt,2);
			correcto = 1;
			crearPuntuacion(puntuaciones, normal, LP);
			
        }
    } while (result == SQLITE_ROW);
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	if (correcto == 1) {
		return SQLITE_OK;
	}
	return SQLITE_ERROR;
}

int borrarPalabras() {
	sqlite3_stmt *stmt;
	char sqlBorrar[] = "DELETE FROM Diccionario";
	int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlBorrar, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error borrando datos\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	return SQLITE_OK;
}

int generarTablas() {
    sqlite3_stmt *stmt;
	char sqlUsuarios[] = "CREATE TABLE IF NOT EXISTS Usuario( \
	Nombre TEXT NOT NULL,\
	Apellido TEXT,\
	Nick TEXT NOT NULL,\
	Contrasenya TEXT NOT NULL,\
	Salt TEXT NOT NULL,\
	PRIMARY KEY(Nick))";

    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlUsuarios, -1, &stmt, NULL);

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia tabla Usuario\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
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

    char sqlPuntuacion[] = "CREATE TABLE IF NOT EXISTS Puntuacion (\
	User_Nick TEXT NOT NULL,\
	Normal_Score INTEGER NOT NULL,\
	League_Points INTEGER NOT NULL)";

    result = sqlite3_prepare_v2(__baseDeDatosActual, sqlPuntuacion, -1, &stmt, NULL) ;  //No estoy seguro del parámetro 3 de la función, si debe ser strlen(sql), strlen(sql)+1, strlen(sql)-1

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia tabla Puntuacion\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
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
    
    char sqlDiccionario[] = "CREATE TABLE IF NOT EXISTS Diccionario (\
	Palabra	TEXT NOT NULL,\
	Tema TEXT NOT NULL,\
	Idioma	TEXT NOT NULL,\
	PRIMARY KEY (Palabra))";

    result = sqlite3_prepare_v2(__baseDeDatosActual, sqlDiccionario, -1, &stmt, NULL);

    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia tabla Diccionario\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
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

    char sqlToken[] = "CREATE TABLE IF NOT EXISTS Token (\
	User_Nick TEXT NOT NULL,\
	Token TEXT NOT NULL,\
    Expira INTEGER NOT NULL,\
	PRIMARY KEY(Token))";

    result = sqlite3_prepare_v2(__baseDeDatosActual, sqlToken, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia tabla Token\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
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
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
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

int meterPalabraBD(char* palabra, char* tematica, char* idioma)
{
	if (existePalabra(palabra)) return SQLITE_ERROR;
	sqlite3_stmt *stmt;
    char sqlPalabra[] = "INSERT INTO diccionario(Palabra, Tema, Idioma) VALUES (?, ?, ?)";
    int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlPalabra, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
    sqlite3_bind_text(stmt, 1, palabra, strlen(palabra), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tematica, strlen(tematica), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, idioma, strlen(idioma), SQLITE_STATIC);
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

int existePalabra(char* palabra){
	sqlite3_stmt *stmt;
	int existe = 0;
	char sqlPalabra[] = "SELECT Palabra FROM Diccionario WHERE Palabra = ?";
	int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlPalabra, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }
	sqlite3_bind_text(stmt, 1, palabra, strlen(palabra), SQLITE_STATIC);
	do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
        	existe = 1;
        }
    } while (result == SQLITE_ROW);
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	if (existe) return SQLITE_ERROR;
	return SQLITE_OK;
	
}

int getPalabraRandom(char* palabra, char* categoria, char* idioma) {
	sqlite3_stmt *stmt;
	char sqlPalabra[] = "SELECT count(*) FROM Diccionario";
	int result = sqlite3_prepare_v2(__baseDeDatosActual, sqlPalabra, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }
	int npalabras;
	do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
        	npalabras = sqlite3_column_int(stmt, 0);
        }
    } while (result == SQLITE_ROW);
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	char sql2[] = "SELECT * FROM Diccionario";
	result = sqlite3_prepare_v2(__baseDeDatosActual, sql2, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
        printf("Error al insertar la sentencia\n");
        return result;
    }
	int r;
	RAND_bytes((unsigned char*) &r, sizeof(int));
	r %= npalabras;
	do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
        	if (r-- != 0) continue;
			strcpy(palabra, (char*) sqlite3_column_text(stmt, 0));
			strcpy(categoria, (char*) sqlite3_column_text(stmt, 1));
			strcpy(idioma, (char*) sqlite3_column_text(stmt, 2));
			break;
        }
    } while (result == SQLITE_ROW);
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(__baseDeDatosActual));
		return result;
	}
	if (r != 0) return SQLITE_ERROR;
	return SQLITE_OK;
}