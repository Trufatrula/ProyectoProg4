#include "usuario.h"
#include "utilidades.h"
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <string.h>

void generarSalt(char* salt) {
    unsigned char buffer[16];
    RAND_bytes(buffer, 16);
    binAHex(buffer, 16, salt);
}

void hashContrasena(char* contrasena, char* salt, char* hash) {
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