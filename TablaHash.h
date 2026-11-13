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
    TablaHash(int cap = 101);   // si cap <= 0 se usa 101
    ~TablaHash();

    void insertar(const std::string& clave, const Estacion& estacion);
    Estacion* buscar(const std::string& clave);
    
    // metodos para obtener información de la tabla
    int getColisiones() const;
    double getFactorCarga() const;
    int getTamano() const;

    // eliminar una estación por su cod
    bool eliminar(const std::string& clave);

    // metodo para obtener todas las estaciones en un arreglo
    int obtenerTodasLasEstaciones(Estacion* arrEstaciones, int capacidadMaxima) const;

    // ordenar y aplicar ordenamiento de insercion
    void ordenarYMostrarPorCapacidad() const;

    void ordenarYMostrarPorBicisDisponibles() const;

    // filtrar estaciones con menos del 20% de ocupación
    void filtrarMenor20PorcientoOcupacion() const;
};

#endif