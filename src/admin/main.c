#include <stdio.h>
#include "menu.h"
#include "../common/consola.h"
#include "../datos/datos.h"
#include "cargarpalabras.h"


int main(void) {
	prepararConsola();
	abrirBD();
	generarTablas();

	menuPrincipalAdmin();

	cerrarBD();
	restaurarConsola();
	return 0;
}

