#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include "NodoHash.h"
#include <string>

class TablaHash {
private:
    int capacidad;       // tamaño
    int tamanoActual;    // cantidad de elementos
    int colisiones;      // cont
    NodoHash** tabla;    // arreglo de punteros a NodoHash

    // funcion hash
    int funcionHash(const std::string& clave) const;

public:
    TablaHash(int cap = 101);
    ~TablaHash();

    void insertar(const std::string& clave, const Estacion& estacion);
    Estacion* buscar(const std::string& clave);
    
    // metodos para obtener información de la tabla
    int getColisiones() const;
    double getFactorCarga() const;
};

#endif