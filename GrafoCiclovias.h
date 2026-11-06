#ifndef GRAFO_CICLOVIAS_H
#define GRAFO_CICLOVIAS_H

#include <string>

struct NodoAdyacencia {
    std::string destinoCodigo;
    NodoAdyacencia* siguiente;

    NodoAdyacencia(std::string dest) : destinoCodigo(dest), siguiente(nullptr) {}
};

struct NodoGrafo {
    std::string codigoEstacion;
    NodoAdyacencia* listaAdyacencia;
    NodoGrafo* siguiente;

    NodoGrafo(std::string cod) : codigoEstacion(cod), listaAdyacencia(nullptr), siguiente(nullptr) {}
};

class GrafoCiclovias {
private:
    NodoGrafo* cabeceraGrafo;

    NodoGrafo* buscarVertice(const std::string& codigo) const;
    NodoGrafo* agregarVertice(const std::string& codigo);

public:
    GrafoCiclovias();
    ~GrafoCiclovias();

    void agregarCiclovia(const std::string& estacionA, const std::string& estacionB);

    void cargarCicloviasDesdeArchivo(const std::string& rutaArchivo);

    void encontrarCaminoMasCorto(const std::string& origen, const std::string& destino) const;
};

#endif