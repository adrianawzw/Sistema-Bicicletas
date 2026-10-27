#include "Sistema.h"

int main() {
    Sistema miSistema;
    
    miSistema.cargarDatos();     // carga los archivos
    miSistema.ejecutarMenu();    // inicia la interacción

    return 0;
}