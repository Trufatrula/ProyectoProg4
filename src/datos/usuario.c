#include "usuario.h"
#include "../common/utilidades.h"
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <string.h>

void generarSalt(char* salt) {
    unsigned char buffer[16];
    RAND_bytes(buffer, 16);
    binAHex(buffer, 16, salt);
}

void hashContrasena(const char* contrasena, const char* salt, char* hash) {
    unsigned char saltBuffer[16];
    unsigned char hashBuffer[SHA256_DIGEST_LENGTH];
    SHA256_CTX context;
    SHA256_Init(&context);
    hexABin(salt, 32, saltBuffer);
    SHA256_Update(&context, saltBuffer, 16);
    SHA256_Update(&context, (unsigned char*) contrasena, strlen(contrasena));
    SHA256_Final(hashBuffer, &context);
    binAHex(hashBuffer, SHA256_DIGEST_LENGTH, hash);
}

void crearUsuario(Usuario* usuario, const char* nombre, const char* apellido, const char* nickname, const char* hash, const char* salt) {
    usuario->nombre = (char*) malloc(strlen(nombre) + 1);
    usuario->apellido = (char*) malloc(strlen(apellido) + 1);
    usuario->nickname = (char*) malloc(strlen(nickname) + 1);
    usuario->hash = (char*) malloc(strlen(hash) + 1);
    usuario->salt = (char*) malloc(strlen(salt) + 1);
    strcpy(usuario->nombre, nombre);
    strcpy(usuario->apellido, apellido);
    strcpy(usuario->nickname, nickname);
    strcpy(usuario->hash, hash);
    strcpy(usuario->salt, salt);
}

void iniciarUsuario(Usuario* usuario, const char* nombre, const char* apellido, const char* nickname, const char* contrasena) {
    usuario->nombre = (char*) malloc(strlen(nombre) + 1);
    usuario->apellido = (char*) malloc(strlen(apellido) + 1);
    usuario->nickname = (char*) malloc(strlen(nickname) + 1);
    usuario->hash = (char*) malloc(65);
    usuario->salt = (char*) malloc(33);
    strcpy(usuario->nombre, nombre);
    strcpy(usuario->apellido, apellido);
    strcpy(usuario->nickname, nickname);
    generarSalt(usuario->salt);
    hashContrasena(contrasena, usuario->salt, usuario->hash);
}

void setContrasena(Usuario* usuario, const char* contrasena) {
    hashContrasena(contrasena, usuario->salt, usuario->hash);
}

void liberarUsuario(Usuario* usuario) {
    free(usuario->nombre);
    free(usuario->apellido);
    free(usuario->nickname);
    free(usuario->hash);
    free(usuario->salt);
}