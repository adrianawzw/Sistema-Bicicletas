#include "GestorColas.h"

GestorColas::GestorColas() : primero(nullptr) {}

GestorColas::~GestorColas()
{
    while (primero != nullptr)
    {
        NodoGestor *temp = primero;
        primero = primero->siguiente;
        delete temp;
    }
}

NodoGestor *GestorColas::buscarNodo(const std::string &codigo) const
{
    NodoGestor *actual = primero;
    while (actual != nullptr)
    {
        if (actual->codigoEstacion == codigo)
            return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

int GestorColas::encolarUsuario(const std::string &codigoEstacion, int dni)
{
    NodoGestor *nodo = buscarNodo(codigoEstacion);
    if (nodo == nullptr)
    {
        nodo = new NodoGestor(codigoEstacion);
        nodo->siguiente = primero;
        primero = nodo;
    }
    if (!nodo->cola.encolar(dni))
    {
        return 0;
    }
    return nodo->cola.getCantidad();
}

bool GestorColas::atenderSiguiente(const std::string &codigoEstacion, int &dni)
{
    NodoGestor *nodo = buscarNodo(codigoEstacion);
    if (nodo == nullptr)
    {
        return false;
    }
    return nodo->cola.desencolar(dni);
}

int GestorColas::cantidadEnEspera(const std::string &codigoEstacion) const
{
    NodoGestor *nodo = buscarNodo(codigoEstacion);
    return (nodo == nullptr) ? 0 : nodo->cola.getCantidad();
}