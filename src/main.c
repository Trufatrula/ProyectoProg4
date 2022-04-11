#include <stdio.h>
#include "menu.h"
#include "consola.h"

int main(void) {
	activarUTF8();

	menuSesion();
	
	desactivarUTF8();
	return 0;
}

