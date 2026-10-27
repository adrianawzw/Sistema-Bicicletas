#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "TablaHash.h" // tabla hash para almacenar estaciones

class Sistema {
private:
    TablaHash tablaEstaciones;

public:
    Sistema();
    ~Sistema();

    void cargarDatos();    // lectura de estaciones.txt
    void ejecutarMenu();   // las opciones por consola
};

#endif