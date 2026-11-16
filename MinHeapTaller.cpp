#include "MinHeapTaller.h"

MinHeapTaller::MinHeapTaller() : datos(nullptr), tamano(0), capacidad(8), contadorOrden(0)
{
    datos = new ElementoTaller[capacidad];
}

MinHeapTaller::~MinHeapTaller()
{
    delete[] datos;
}

// a es mas urgente que b si tiene menor prioridad; si empatan, el que llego antes
bool MinHeapTaller::esMasUrgente(const ElementoTaller &a, const ElementoTaller &b) const
{
    if (a.prioridad != b.prioridad)
    {
        return a.prioridad < b.prioridad;
    }
    return a.orden < b.orden;
}

void MinHeapTaller::subir(int i)
{
    while (i > 0)
    {
        int padre = (i - 1) / 2;
        if (!esMasUrgente(datos[i], datos[padre]))
        {
            break;
        }
        ElementoTaller temp = datos[i];
        datos[i] = datos[padre];
        datos[padre] = temp;
        i = padre;
    }
}

void MinHeapTaller::bajar(int i)
{
    while (true)
    {
        int izq = 2 * i + 1;
        int der = 2 * i + 2;
        int menor = i;

        if (izq < tamano && esMasUrgente(datos[izq], datos[menor]))
        {
            menor = izq;
        }
        if (der < tamano && esMasUrgente(datos[der], datos[menor]))
        {
            menor = der;
        }
        if (menor == i)
        {
            break;
        }
        ElementoTaller temp = datos[i];
        datos[i] = datos[menor];
        datos[menor] = temp;
        i = menor;
    }
}

void MinHeapTaller::duplicarCapacidad()
{
    int nuevaCapacidad = capacidad * 2;
    ElementoTaller *nuevo = new ElementoTaller[nuevaCapacidad];
    for (int i = 0; i < tamano; i++)
    {
        nuevo[i] = datos[i];
    }
    delete[] datos;
    datos = nuevo;
    capacidad = nuevaCapacidad;
}

bool MinHeapTaller::insertar(int biciId, int prioridad)
{
    if (prioridad < 1 || prioridad > 3)
    {
        return false; // mantiene el invariante de prioridad
    }
    if (tamano == capacidad)
    {
        duplicarCapacidad();
    }
    datos[tamano].biciId = biciId;
    datos[tamano].prioridad = prioridad;
    datos[tamano].orden = contadorOrden++;
    subir(tamano);
    tamano++;
    return true;
}

bool MinHeapTaller::extraerMasUrgente(ElementoTaller &resultado)
{
    if (tamano == 0)
    {
        return false;
    }
    resultado = datos[0];
    tamano--;
    datos[0] = datos[tamano];
    bajar(0);
    return true;
}

bool MinHeapTaller::estaVacio() const
{
    return tamano == 0;
}

int MinHeapTaller::getTamano() const
{
    return tamano;
}