#include "ColaBFS.h"

// constructor del NodoCola
NodoCola::NodoCola(std::string cod, int dist) {
    codigoEstacion = cod;
    distancia = dist;
    siguiente = nullptr;
}

// constructor de la ColaBFS
ColaBFS::ColaBFS() {
    frente = nullptr;
    final = nullptr;
}

// destructor
ColaBFS::~ColaBFS() {
    std::string dummyCod;
    int dummyDist;
    while (!estaVacia()) {
        desencolar(dummyCod, dummyDist);
    }
}

bool ColaBFS::estaVacia() const {
    return frente == nullptr;
}

void ColaBFS::encolar(std::string cod, int dist) {
    NodoCola* nuevo = new NodoCola(cod, dist);
    if (estaVacia()) {
        frente = final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }
}

void ColaBFS::desencolar(std::string& cod, int& dist) {
    if (estaVacia()) {
        cod = "";
        dist = -1;
        return;
    }
    NodoCola* temp = frente;
    cod = temp->codigoEstacion;
    dist = temp->distancia;
    frente = frente->siguiente;
    if (frente == nullptr) final = nullptr;
    delete temp;
}