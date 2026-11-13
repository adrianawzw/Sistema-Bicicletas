#ifndef NODO_ARBOL_BICI_H
#define NODO_ARBOL_BICI_H

#include "Bicicleta.h"

struct NodoArbolBici {
    Bicicleta dato;
    NodoArbolBici* izquierdo;
    NodoArbolBici* derecho;

    explicit NodoArbolBici(const Bicicleta& bici)
        : dato(bici), izquierdo(nullptr), derecho(nullptr) {}
};

#endif