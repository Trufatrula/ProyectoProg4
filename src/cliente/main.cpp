#include <iostream>
#include "juego.h"
#define RED "\e[0;31m"
int main() {
    //std::cout << "hola genteeeeeee\n";
    Partida p = Partida("cacahuete");
    p.comprobarResultado("cacahuete","*/*--**//");
    //std::cout << RED "Jorge la xupa"  << std::endl;
    return 0;
}