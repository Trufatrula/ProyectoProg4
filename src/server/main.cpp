#include <iostream>
#include <thread>
#include "../common/consola.h"
#include "../datos/datos.h"
#include "../sockets/incluir.h"
#include "../sockets/tcom.h"

#define PUERTO 6969
#define HOST   "localhost"

int main() {
    prepararConsola();
    abrirBD();
	generarTablas();
    sockaddr_in server;
    SOCKET srvsock;
    #ifdef __WIN32
    WSADATA wsaData;
    std::cout << "Iniciando WinSock..." << std::endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Error iniciando WinSock" << std::endl;
        cerrarBD();
        restaurarConsola();
		return -1;
	}
    #endif
    std::cout << "Servidor iniciado" << std::endl;
    if ((srvsock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		std::cerr << "No se puede crear el socket" << std::endl;
        #ifdef __WIN32
		WSACleanup();
        #endif
        cerrarBD();
        restaurarConsola();
		return -1;
	}

    std::cout << "Socket creado" << std::endl;

    server.sin_family = AF_INET;
    server.sin_port = PUERTO;
    setupAddrStruct(HOST, &server.sin_addr);

    if (bind(srvsock, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		std::cerr << "No se ha podido bindear el socket" << std::endl;
		closesocket(srvsock);
        #ifdef __WIN32
		WSACleanup();
        #endif
        cerrarBD();
        restaurarConsola();
		return -1;
	}

    std::cout << "Socket bindeado al puerto y el host" << std::endl;

    if (listen(srvsock, 64) == SOCKET_ERROR) {
		std::cerr << "No se puede poner el socket a escucha" << std::endl;
		closesocket(srvsock);
        #ifdef __WIN32
		WSACleanup();
        #endif
        cerrarBD();
        restaurarConsola();
		return -1;
	}

    std::cout << "Escuchando en " << HOST << ":" << PUERTO << std::endl;
    
    while (true) {
        socklen_t stsize = sizeof(struct sockaddr);
        struct sockaddr_in addr;
        SOCKET socket = accept(srvsock, (struct sockaddr*) &addr, &stsize);
        if (socket == INVALID_SOCKET) {
		    std::cerr << "No se ha podido aceptar la conexión" << std::endl;
		    closesocket(srvsock);
            #ifdef __WIN32
		    WSACleanup();
            #endif
            cerrarBD();
            restaurarConsola();
		    return -1;
	    }
        //hilo e incoming
    }

    closesocket(srvsock);
    #ifdef __WIN32
    WSACleanup();
    #endif

    cerrarBD();
    restaurarConsola();
    return 0;
}