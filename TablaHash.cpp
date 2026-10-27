#include "TablaHash.h"
#include <iostream>

TablaHash::TablaHash(int cap) {
    capacidad = cap;
    tamanoActual = 0;
    colisiones = 0;
    tabla = new NodoHash*[capacidad];
    
    // inicializar
    for (int i = 0; i < capacidad; i++) {
        tabla[i] = nullptr;
    }
}

TablaHash::~TablaHash() {
    for (int i = 0; i < capacidad; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            NodoHash* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
    delete[] tabla;
}

// funcion hash para los valores ascII de la clave y aplicar módulo
int TablaHash::funcionHash(const std::string& clave) const {
    int suma = 0;
    for (char c : clave) {
        suma += static_cast<int>(c);
    }
    return suma % capacidad;
}

// inserta una estación en la tabla hash
void TablaHash::insertar(const std::string& clave, const Estacion& estacion) {
    int indice = funcionHash(clave);
    
    NodoHash* nuevoNodo = new NodoHash(clave, estacion);

    // si esta posición esta vacía insertamos directamente
    if (tabla[indice] == nullptr) {
        tabla[indice] = nuevoNodo;
    } else {
        // si hay colision
        colisiones++;
        nuevoNodo->siguiente = tabla[indice]; // insertamos al inicio de la lista enlazada
        tabla[indice] = nuevoNodo;
    }
    tamanoActual++;
}

// busca una estación por su clave.codigo
Estacion* TablaHash::buscar(const std::string& clave) {
    int indice = funcionHash(clave);
    NodoHash* actual = tabla[indice];

    while (actual != nullptr) {
        if (actual->clave == clave) {
            return &(actual->estacion); // se retorna el puntero a la estación encontrada
        }
        actual = actual->siguiente;
    }
    return nullptr; // no se encuentra
}

// para obtener información de la tabla
int TablaHash::getColisiones() const {
    return colisiones;
}

double TablaHash::getFactorCarga() const {
    return static_cast<double>(tamanoActual) / capacidad;
}