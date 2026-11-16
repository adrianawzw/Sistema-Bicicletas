#ifndef LISTA_VIAJES_H
#define LISTA_VIAJES_H

#include "Viaje.h"
#include <string>

struct NodoViaje
{
    Viaje viaje;
    NodoViaje *siguiente;

    NodoViaje(const Viaje &v) : viaje(v), siguiente(nullptr) {}
};

class ListaViajes
{
private:
    NodoViaje *primero;
    NodoViaje *ultimo;
    int cantidad;

public:
    ListaViajes();
    ~ListaViajes();

    // la lista maneja memoria dinamica: no se permite copiar
    ListaViajes(const ListaViajes &) = delete;
    ListaViajes &operator=(const ListaViajes &) = delete;

    void agregar(const Viaje &v); // O(1)
    void cargarDesdeArchivo(const std::string &ruta);

    // B1: viajes que salieron de una estacion entre dos fechas (inclusive)
    int contarViajesPorEstacion(const std::string &codigo, int desde, int hasta) const; // O(n)

    // B2: lista los viajes de un DNI y devuelve el total de minutos
    int mostrarViajesPorUsuario(int dni) const; // O(n)
};

#endif