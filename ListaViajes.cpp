#include "ListaViajes.h"
#include <iostream>
#include <fstream>

ListaViajes::ListaViajes() : primero(nullptr), ultimo(nullptr), cantidad(0) {}

ListaViajes::~ListaViajes()
{
    while (primero != nullptr)
    {
        NodoViaje *temp = primero;
        primero = primero->siguiente;
        delete temp;
    }
}

void ListaViajes::agregar(const Viaje &v)
{
    NodoViaje *nuevo = new NodoViaje(v);
    if (primero == nullptr)
    {
        primero = ultimo = nuevo;
    }
    else
    {
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
    cantidad++;
}

void ListaViajes::cargarDesdeArchivo(const std::string &ruta)
{
    std::ifstream archivo(ruta);
    if (!archivo.is_open())
    {
        std::cerr << "Error! No se pudo abrir " << ruta << "\n";
        return;
    }

    int id, bici, dni, fecha, dur;
    std::string origen, destino;
    int cargados = 0;
    while (archivo >> id >> bici >> dni >> origen >> destino >> fecha >> dur)
    {
        agregar(Viaje(id, bici, dni, origen, destino, fecha, dur));
        cargados++;
    }
    archivo.close();
    std::cout << "Viajes cargados: " << cargados << "\n";
}

int ListaViajes::contarViajesPorEstacion(const std::string &codigo, int desde, int hasta) const
{
    int contador = 0;
    NodoViaje *actual = primero;
    while (actual != nullptr)
    {
        const Viaje &v = actual->viaje;
        if (v.getEstacionOrigen() == codigo && v.getFecha() >= desde && v.getFecha() <= hasta)
        {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

int ListaViajes::mostrarViajesPorUsuario(int dni) const
{
    int totalMinutos = 0;
    int encontrados = 0;
    NodoViaje *actual = primero;
    while (actual != nullptr)
    {
        if (actual->viaje.getDniUsuario() == dni)
        {
            actual->viaje.mostrar();
            totalMinutos += actual->viaje.getDuracionMin();
            encontrados++;
        }
        actual = actual->siguiente;
    }
    if (encontrados == 0)
    {
        std::cout << "No hay viajes para ese DNI.\n";
    }
    return totalMinutos;
}