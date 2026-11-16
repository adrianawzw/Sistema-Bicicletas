#include "ColaEspera.h"

ColaEspera::ColaEspera() : frente(nullptr), final(nullptr), cantidad(0) {}

ColaEspera::~ColaEspera()
{
    while (frente != nullptr)
    {
        NodoEspera *temp = frente;
        frente = frente->siguiente;
        delete temp;
    }
}

bool ColaEspera::contiene(int dni) const
{
    NodoEspera *actual = frente;
    while (actual != nullptr)
    {
        if (actual->dni == dni)
            return true;
        actual = actual->siguiente;
    }
    return false;
}

bool ColaEspera::encolar(int dni)
{
    if (contiene(dni))
    {
        return false; // mantiene el invariante: sin DNIs repetidos
    }
    NodoEspera *nuevo = new NodoEspera(dni);
    if (frente == nullptr)
    {
        frente = final = nuevo;
    }
    else
    {
        final->siguiente = nuevo;
        final = nuevo;
    }
    cantidad++;
    return true;
}

bool ColaEspera::desencolar(int &dni)
{
    if (frente == nullptr)
    {
        return false;
    }
    NodoEspera *temp = frente;
    dni = temp->dni;
    frente = frente->siguiente;
    if (frente == nullptr)
    {
        final = nullptr;
    }
    delete temp;
    cantidad--;
    return true;
}

bool ColaEspera::estaVacia() const
{
    return frente == nullptr;
}

int ColaEspera::getCantidad() const
{
    return cantidad;
}