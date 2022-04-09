#include <stdio.h>
#include "menu.h"

int main(void)
{
	char opcion;

	do{
		opcion = mostarMenuUsuario();
		switch (opcion){
			case '1':
            printf("hola");
				break;
			case '2':
				break;
		}
	}while(opcion != '3');
	return 0;
}