#include <stdio.h>
#include <sqlite3.h>
#include "menu.h"
#include "consola.h"
#include "utilidades.h"

int main(void)
{
	activarUTF8();

	char hex[] = "234ff00dda";
	unsigned char bin[5] = {0};
	char backHex[11] = {0};

	hexABin(hex, 10, bin);
	binAHex(bin, 5, backHex);
	printf("%s\n", backHex);

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

