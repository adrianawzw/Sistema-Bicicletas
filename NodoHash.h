#ifndef NODO_HASH_H
#define NODO_HASH_H

#include <string>
#include "Estacion.h"

struct NodoHash {
    std::string clave;    // codiog
    Estacion estacion;    // estación
    NodoHash* siguiente;  // puntero

    // Constructor
    NodoHash(std::string c, Estacion est) : clave(c), estacion(est), siguiente(nullptr) {}
};

#endif