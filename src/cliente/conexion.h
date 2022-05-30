#ifndef CLIENTECONEXION
#define CLIENTECONEXION

#ifdef __cplusplus
extern "C" {
#endif

#include "../sockets/incluir.h"

extern SOCKET socket_cliente;

int conectar(const char* host, unsigned short puerto);
int desconectar();

#ifdef __cplusplus
}
#endif


#endif