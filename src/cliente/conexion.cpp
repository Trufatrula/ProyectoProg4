#include "conexion.h"
#include "../sockets/tcom.h"
#include <iostream>

SOCKET socket_cliente = -1;

int conectar(const char* host, unsigned short puerto) {
    sockaddr_in server;
    #ifdef __WIN32
    WSADATA wsaData;
    std::cout << "Iniciando WinSock..." << std::endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Error iniciando WinSock" << std::endl;
		return -1;
	}
    #endif

    if ((socket_cliente = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		std::cerr << "No se puede crear el socket" << std::endl;
        #ifdef __WIN32
		WSACleanup();
        #endif
		return 1;
	}
 
	server.sin_family = AF_INET;
	server.sin_port = htons(puerto);
    setupAddrStruct(host, &server.sin_addr);

	//CONNECT to remote server
	if (connect(socket_cliente, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		std::cerr << "Error al conectarse al servidor" << std::endl;
		closesocket(socket_cliente);
        #ifdef __WIN32
		WSACleanup();
        #endif
		return -1;
	}

    return 0;


}

int desconectar() {
    closesocket(socket_cliente);
    socket_cliente = -1;
    return 0;
}