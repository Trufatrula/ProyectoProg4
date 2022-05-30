#include <iostream>
#include "../common/consola.h"
#include "menu.h"

int main() {

    prepararConsola();
    menuRegistro(  );
    /*
    if (menuInicio() == 0) {
        menuCliente();

    }
    */
    restaurarConsola();
    return 0;
}