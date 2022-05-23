#include <stdio.h>
#include "menu.h"
#include "../common/consola.h"
#include "../datos/datos.h"


int main(void) {
	activarUTF8();
	abrirBD();
	generarTablas();
	cargarPalabrasABaseDeDatosAdmin();

	//menuPrincipalAdmin();

	cerrarBD();
	desactivarUTF8();
	return 0;
}

