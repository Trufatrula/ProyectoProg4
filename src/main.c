#include <stdio.h>
#include "menu.h"
#include "consola.h"
#include "datos.h"


int main(void) {
	activarUTF8();
	abrirBD();
	generarTablas();

	if(menuSesion() == 1){
		cerrarBD();
		desactivarUTF8();
		return 0;
	}
	menuPrincipal();
	
	cerrarBD();
	desactivarUTF8();
	return 0;
}

