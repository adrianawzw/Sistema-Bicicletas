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

    // submenus
    void menuEstaciones();   // tabla hash + grafo
    void menuBicicletas();   // arbol de bicicletas

    // opciones del Menu Estaciones
    void mostrarEstacion();
    void agregarEstacion();
    void eliminarEstacion();
    void caminoMinimo();
    void mostrarEstadisticasHash();

    // opciones del Menu Bicicletas
    void insertarBicicleta();
    void buscarBicicleta();
    void eliminarBicicleta();

public:
    Sistema();
    ~Sistema();

    void cargarDatos();    // lectura de estaciones.txt, ciclovias.txt y bicicletas.txt
    void ejecutarMenu();   // Menu Principal
};

#endif
