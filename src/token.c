#include "token.h"
#include "utilidades.h"
#include <openssl/rand.h>

void generateToken(char* token) {
    unsigned char tokenBuffer[16];
    RAND_bytes(tokenBuffer, 16);
    binAHex(tokenBuffer, 16, token);
}