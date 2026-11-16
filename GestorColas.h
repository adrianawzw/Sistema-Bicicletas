#ifndef GESTOR_COLAS_H
#define GESTOR_COLAS_H

#include "ColaEspera.h"
#include <string>

struct NodoGestor
{
    std::string codigoEstacion;
    ColaEspera cola;
    NodoGestor *siguiente;

    NodoGestor(const std::string &cod) : codigoEstacion(cod), siguiente(nullptr) {}
};

class GestorColas
{
    // Invariante: hay a lo sumo un nodo por codigo de estacion
private:
    NodoGestor *primero;

    NodoGestor *buscarNodo(const std::string &codigo) const;

public:
    GestorColas();
    ~GestorColas();

    GestorColas(const GestorColas &) = delete;
    GestorColas &operator=(const GestorColas &) = delete;

    // encola al usuario en la estacion; devuelve la posicion (1 = primero) o 0 si ya estaba
    int encolarUsuario(const std::string &codigoEstacion, int dni);

    // saca al primero de la cola de esa estacion; false si no hay nadie esperando
    bool atenderSiguiente(const std::string &codigoEstacion, int &dni);

    int cantidadEnEspera(const std::string &codigoEstacion) const;
};

#endif