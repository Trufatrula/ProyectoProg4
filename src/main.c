#include <stdio.h>
#include "menu.h"

int main(void)
{
	char opcion;
	char opcion2;
	char usuario;

	do{
		opcion = mostrarMenuUsuario();
		switch (opcion){
			case '1':
            printf("hola");
				break;
			case '2':
				break;
		}
	}while(opcion != '3');

	/*
	do{
		opcion2 = mostrarMenuCuenta(&usuario); //Le tenemos que pasar el usuario seleccionado o creado en el menu anterior.
		switch (opcion2){
			case '1':
            printf("hola");
				break;
			case '2':
				break;
			case '3':
				break;
		}
	}while(opcion2 != '4');
	*/
	
	
	return 0;

}

