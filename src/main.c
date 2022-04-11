#include <stdio.h>
#include <sqlite3.h>
#include "menu.h"
#include "consola.h"

int main(void)
{
	activarUTF8();

	return 0;
	menuSesion();

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
	
	desactivarUTF8();
	return 0;

}

