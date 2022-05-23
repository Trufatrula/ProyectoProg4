#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"
#include "../datos/datos.h"
#include "cargarpalabras.h"

int cargarPalabrasABaseDeDatosAdmin() {
    CSV csv;
    if(loadCSV(&csv, "palabras.csv") == 1) {
        return 1;
    }

    if(borrarPalabras() == SQLITE_ERROR) {
        freeCSV(&csv);
        return 1;
    }

    unsigned long rows = getRowCountCSV(&csv);

    for(unsigned long i = 0; i < rows; i++) {
        if(getColumnCountCSV(&csv, i) != 3) {
            freeCSV(&csv);
            return 1;
        }
        char* palabra = getValueCSV(&csv, i, 0);
        char* tema = getValueCSV(&csv, i, 1);
        char* idioma = getValueCSV(&csv, i, 2);
        if(meterPalabraBD(palabra, tema, idioma) == SQLITE_ERROR){
            freeCSV(&csv);
            return 1;
        }
    }
}

