#include <iostream>
#include "juego.h"
#include "../common/consola.h"
int main() {
    prepararConsola();
    //std::cout << "hola genteeeeeee\n";
    Partida p = Partida();
    p.comprobarResultado("cacahuete","*/*--**//");
    //std::cout << RED "Jorge la xupa"  << std::endl;
    restaurarConsola();
    return 0;
}