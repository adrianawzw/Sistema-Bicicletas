#include "GrafoCiclovias.h"
#include "ColaBFS.h"
#include <iostream>
#include <fstream>

GrafoCiclovias::GrafoCiclovias() : cabeceraGrafo(nullptr) {}

GrafoCiclovias::~GrafoCiclovias() {
    NodoGrafo* actualVertice = cabeceraGrafo;
    while (actualVertice != nullptr) {
        // para liberar la memoria de la lista de adyacencia de cada vertice
        NodoAdyacencia* actualAdy = actualVertice->listaAdyacencia;
        while (actualAdy != nullptr) {
            NodoAdyacencia* tempAdy = actualAdy;
            actualAdy = actualAdy->siguiente;
            delete tempAdy;
        }
        NodoGrafo* tempVertice = actualVertice;
        actualVertice = actualVertice->siguiente;
        delete tempVertice;
    }
}

NodoGrafo* GrafoCiclovias::buscarVertice(const std::string& codigo) const {
    NodoGrafo* actual = cabeceraGrafo;
    while (actual != nullptr) {
        if (actual->codigoEstacion == codigo) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

NodoGrafo* GrafoCiclovias::agregarVertice(const std::string& codigo) {
    NodoGrafo* existente = buscarVertice(codigo);
    if (existente != nullptr) return existente;

    NodoGrafo* nuevo = new NodoGrafo(codigo);
    nuevo->siguiente = cabeceraGrafo;
    cabeceraGrafo = nuevo;
    return nuevo;
}

void GrafoCiclovias::agregarCiclovia(const std::string& estacionA, const std::string& estacionB) {
    // invariante: sin lazos y sin aristas repetidas
    if (estacionA == estacionB) return;
    if (existeCiclovia(estacionA, estacionB)) return;

    NodoGrafo* verticeA = agregarVertice(estacionA);
    NodoGrafo* verticeB = agregarVertice(estacionB);

    // se agrega en ambos sentidos
    NodoAdyacencia* nuevoAdyA = new NodoAdyacencia(estacionB);
    nuevoAdyA->siguiente = verticeA->listaAdyacencia;
    verticeA->listaAdyacencia = nuevoAdyA;

    NodoAdyacencia* nuevoAdyB = new NodoAdyacencia(estacionA);
    nuevoAdyB->siguiente = verticeB->listaAdyacencia;
    verticeB->listaAdyacencia = nuevoAdyB;
}

// cargar el archivo txt
void GrafoCiclovias::cargarCicloviasDesdeArchivo(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << rutaArchivo << std::endl;
        return;
    }

    std::string estacionA, estacionB;
    while (archivo >> estacionA >> estacionB) {
        agregarCiclovia(estacionA, estacionB);
    }

    archivo.close();
    std::cout << "¡Red de ciclovias cargada exitosamente en el Grafo!" << std::endl;
}

// implementacion de bfs
void GrafoCiclovias::encontrarCaminoMasCorto(const std::string& origen, const std::string& destino) const {
    NodoGrafo* vOrigen = buscarVertice(origen);
    NodoGrafo* vDestino = buscarVertice(destino);

    if (vOrigen == nullptr || vDestino == nullptr) {
        std::cout << "Error: La estacion de origen o destino no existe en el grafo de ciclovias." << std::endl;
        return;
    }

    if (origen == destino) {
        std::cout << "La estacion de origen y destino son la misma. Tramos: 0" << std::endl;
        return;
    }

    // guardar los nodos visitados
    struct NodoVisitado {
        std::string codigo;
        std::string padre; // Para reconstruir el camino si se desea
        NodoVisitado* siguiente;
        NodoVisitado(std::string cod, std::string pad) : codigo(cod), padre(pad), siguiente(nullptr) {}
    };

    NodoVisitado* visitados = nullptr;

    auto estaVisitado = [&visitados](const std::string& cod) {
        NodoVisitado* act = visitados;
        while (act != nullptr) {
            if (act->codigo == cod) return true;
            act = act->siguiente;
        }
        return false;
    };

    auto marcarVisitado = [&visitados](const std::string& cod, const std::string& pad) {
        NodoVisitado* nuevo = new NodoVisitado(cod, pad);
        nuevo->siguiente = visitados;
        visitados = nuevo;
    };

    ColaBFS cola;
    cola.encolar(origen, 0);
    marcarVisitado(origen, "");

    bool encontrado = false;

    while (!cola.estaVacia()) {
        std::string actualCod;
        int distanciaActual;
        cola.desencolar(actualCod, distanciaActual);

        if (actualCod == destino) {
            std::cout << "\nCamino encontrado!" << std::endl;
            std::cout << "Cantidad minima de tramos (saltos): " << distanciaActual << std::endl;
            encontrado = true;
            break;
        }

        NodoGrafo* vActual = buscarVertice(actualCod);
        if (vActual != nullptr) {
            NodoAdyacencia* ady = vActual->listaAdyacencia;
            while (ady != nullptr) {
                if (!estaVisitado(ady->destinoCodigo)) {
                    marcarVisitado(ady->destinoCodigo, actualCod);
                    cola.encolar(ady->destinoCodigo, distanciaActual + 1);
                }
                ady = ady->siguiente;
            }
        }
    }

    if (!encontrado) {
        std::cout << "\nNo existe un recorrido por ciclovias entre " << origen << " y " << destino << "." << std::endl;
    }

    // limpiar la memoria de los nodos visitados
    while (visitados != nullptr) {
        NodoVisitado* temp = visitados;
        visitados = visitados->siguiente;
        delete temp;
    }
}

bool GrafoCiclovias::existeCiclovia(const std::string& estacionA, const std::string& estacionB) const {
    NodoGrafo* vA = buscarVertice(estacionA);
    if (vA == nullptr) return false;

    NodoAdyacencia* ady = vA->listaAdyacencia;
    while (ady != nullptr) {
        if (ady->destinoCodigo == estacionB) return true;
        ady = ady->siguiente;
    }
    return false;
}