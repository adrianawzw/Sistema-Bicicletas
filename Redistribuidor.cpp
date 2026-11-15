#include "Redistribuidor.h"
#include <iostream>

Redistribuidor::Redistribuidor(int capacidad) {
    // la capacidad no puede ser negativa
    capacidadCamion = (capacidad > 0) ? capacidad : 0;
}

void Redistribuidor::setCapacidadCamion(int capacidad) {
    if (capacidad >= 0) {
        capacidadCamion = capacidad;
    }
}

void Redistribuidor::buscarSubconjuntos(const FaltanteEstacion* estaciones, int n) const {
    if (n <= 0) {
        std::cout << "No hay estaciones para redistribuir.\n";
        return;
    }
    if (capacidadCamion == 0) {
        std::cout << "La capacidad del camion es 0. No hay nada que buscar.\n";
        return;
    }

    // arreglo auxiliar para guardar los índices seleccionados
    // su tamaño máximo posible es n (si se eligen todas las estaciones)
    int* seleccionados = new int[n];
    bool encontrado = false;

    std::cout << "\nSoluciones para capacidad de camion C = " << capacidadCamion << "\n";

    buscarSubconjuntosRec(estaciones, n, 0, 0, seleccionados, 0, encontrado);

    if (!encontrado) {
        std::cout << "No se encontro ninguna combinacion de estaciones que sume exactamente " << capacidadCamion << ".\n";
    } else {
        std::cout << "Fin de las soluciones.\n";
    }

    delete[] seleccionados; 
}

void Redistribuidor::buscarSubconjuntosRec(const FaltanteEstacion* estaciones, int n, 
                                           int indice, int sumaActual,
                                           int* seleccionados, int cantSeleccionados,
                                           bool& encontrado) const {
    // encontramos una combinación exacta
    if (sumaActual == capacidadCamion) {
        encontrado = true;
        std::cout << "{ ";
        for (int i = 0; i < cantSeleccionados; i++) {
            std::cout << estaciones[seleccionados[i]].codigo;
            if (i < cantSeleccionados - 1) std::cout << ", ";
        }
        std::cout << " }\n";
        return;
    }

    // nos pasamos de la capacidad o nos quedamos sin estaciones
    if (sumaActual > capacidadCamion || indice == n) {
        return; // Poda
    }

    buscarSubconjuntosRec(estaciones, n, indice + 1, sumaActual,
                          seleccionados, cantSeleccionados, encontrado);

    seleccionados[cantSeleccionados] = indice; // guardamos el índice
    buscarSubconjuntosRec(estaciones, n, indice + 1, sumaActual + estaciones[indice].faltante,
                          seleccionados, cantSeleccionados + 1, encontrado);
}