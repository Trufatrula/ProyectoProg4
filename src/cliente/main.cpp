#include <iostream>
#include "juego.h"
#include "../sockets/incluir.h"
#include "../sockets/tcom.h"
#include "../common/consola.h"

#define PUERTO 6969
#define HOST   "localhost"

int main() {

    prepararConsola();
    sockaddr_in server;
    SOCKET srvsock;
    #ifdef __WIN32
    WSADATA wsaData;
    std::cout << "Iniciando WinSock..." << std::endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Error iniciando WinSock" << std::endl;
        restaurarConsola();
		return -1;
	}
    #endif

    if ((srvsock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		std::cerr << "No se puede crear el socket" << std::endl;
        #ifdef __WIN32
		WSACleanup();
        #endif
        restaurarConsola();
		return -1;
	}

    std::cout << "Socket creado" << std::endl;



    
	server.sin_family = AF_INET;
	server.sin_port = htons(PUERTO);
    setupAddrStruct(HOST, &server.sin_addr);

	//CONNECT to remote server
	if (connect(srvsock, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		std::cerr << "Error al conectarse al servidor" << std::endl;
		closesocket(srvsock);
        #ifdef __WIN32
		WSACleanup();
        #endif
		return -1;
	}

    std::cout << "Connection stablished with: " << inet_ntoa(server.sin_addr) << "(" << ntohs(server.sin_port) << ")" << std::endl;






    //std::cout << "hola genteeeeeee\n";
    //Partida p = Partida();
    //p.comprobarResultado("cacahuete","*/*--**//");
    //std::cout << RED "Jorge la xupa"  << std::endl;
    //restaurarConsola();
    //return 0;
}