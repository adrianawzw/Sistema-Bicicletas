#ifndef NODO_ARBOL_BICI_H
#define NODO_ARBOL_BICI_H

#include "Bicicleta.h"

// NodoArbolBici representa un nodo en el árbol binario de búsqueda de bicicletas.
struct NodoArbolBici {
    Bicicleta dato;
    NodoArbolBici* izquierdo; // Puntero al hijo izquierdo
    NodoArbolBici* derecho; // Puntero al hijo derecho

    // Constructor que inicializa el nodo con una bicicleta y establece los punteros a nullptr.
    explicit NodoArbolBici(const Bicicleta& bici)
        : dato(bici), izquierdo(nullptr), derecho(nullptr) {}
};

#endif