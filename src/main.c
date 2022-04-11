#include <stdio.h>
#include <sqlite3.h>
#include "menu.h"
#include "consola.h"
#include "usuario.h"

int main(void) {
	activarUTF8();

	menuSesion();
	
	desactivarUTF8();
	return 0;
}

