#include <stdio.h>
#include "menu.h"
#include "../common/consola.h"
#include "../datos/datos.h"
#include "cargarpalabras.h"


int main(void) {
	prepararConsola();
	abrirBD();
	generarTablas();
	
	char a[100];
	char b[100];
	char c[100];

	getPalabraRandom(a, b, c);
	printf("%s %s %s\n", a, b, c);

	menuPrincipalAdmin();

	cerrarBD();
	restaurarConsola();
	return 0;
}

