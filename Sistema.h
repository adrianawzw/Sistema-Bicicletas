#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "TablaHash.h" // tabla hash para almacenar estaciones
#include "GrafoCiclovias.h" // grafo para representar ciclovías
#include "ArbolBicicletas.h" // arbol para almacenar bicicletas

class Sistema {
private:
    TablaHash tablaEstaciones;
    GrafoCiclovias grafoRed; // ciclovias modulo A
    ArbolBicicletas arbolBicis; // arbol de bicicletas modulo B
    void menuBicicletas(); // menu para el arbol de bicicletas

public:
    Sistema();
    ~Sistema();

    void cargarDatos();    // lectura de estaciones.txt
    void ejecutarMenu();   // las opciones por consola
};

#endif