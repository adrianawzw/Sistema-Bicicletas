#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "TablaHash.h"       // tabla hash para almacenar estaciones
#include "GrafoCiclovias.h"  // grafo para representar ciclovías
#include "ArbolBicicletas.h" // arbol para almacenar bicicletas
#include "ListaViajes.h"     // lista enlazada para almacenar viajes
#include "GestorColas.h"     // B4: colas de espera por estacion
#include "MinHeapTaller.h"   // NUEVO (B5): cola de prioridad del taller
#include "Redistribuidor.h"

class Sistema
{
private:
    TablaHash tablaEstaciones;
    GrafoCiclovias grafoRed;          // ciclovias modulo A
    ArbolBicicletas arbolBicis;       // arbol de bicicletas modulo C
    ListaViajes listaViajes;          // viajes modulo B
    GestorColas gestorColas;          // B4: colas de espera por estacion
    MinHeapTaller tallerReparaciones; // NUEVO (B5): taller de reparaciones

    // submenus
    void menuEstaciones(); // tabla hash + grafo
    void menuBicicletas(); // arbol de bicicletas
    void menuViajes();     // modulo B

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

    // opciones del Menu Viajes
    void contarViajesEstacion();
    void buscarViajesUsuario();
    void listarBicisMasDeKm(); // B3
    void retirarBici();        // B4
    void devolverBici();       // B4
    void enviarATaller();      // NUEVO (B5)
    void atenderTaller();      // NUEVO (B5)

    void menuRedistribucion();

public:
    Sistema();
    ~Sistema();

    void cargarDatos();  // lectura de estaciones.txt, ciclovias.txt, bicicletas.txt y viajes.txt
    void ejecutarMenu(); // Menu Principal
};

#endif