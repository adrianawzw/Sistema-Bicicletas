#include "Sistema.h"
#include <iostream>
#include <fstream>
#include "Estacion.h"

Sistema::Sistema() : tablaEstaciones(101) {
}

void Sistema::cargarDatos() {
    std::ifstream archivo("estaciones.txt");
    
    if (!archivo.is_open()) {
        std::cerr << "Error! No se pudo abrir el archivo estaciones.txt" << std::endl;
        return;
    }

    std::string codigo, nombre, barrio;
    int capacidadAnclajes, bicisDisponibles;

    while (archivo >> codigo >> nombre >> barrio >> capacidadAnclajes >> bicisDisponibles) {
        Estacion nuevaEstacion(codigo, nombre, barrio, capacidadAnclajes, bicisDisponibles);
        tablaEstaciones.insertar(codigo, nuevaEstacion);
    }

    archivo.close();
    std::cout << "Estaciones cargadas exitosamente desde Sistema::cargarDatos()!" << std::endl;
}

void Sistema::ejecutarMenu() {
    // falta implementar
}