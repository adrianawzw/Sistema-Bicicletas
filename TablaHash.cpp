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
    // validar duplicado antes de insertar
    if (buscar(clave) != nullptr) {
        return; // ya existe, no insertar
    }

    int indice = funcionHash(clave);
    NodoHash* nuevoNodo = new NodoHash(clave, estacion);

    if (tabla[indice] == nullptr) {
        tabla[indice] = nuevoNodo;
    } else {
        colisiones++;
        nuevoNodo->siguiente = tabla[indice];
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

int TablaHash::getTamano() const { return tamanoActual; }  

double TablaHash::getFactorCarga() const {
    return static_cast<double>(tamanoActual) / capacidad;
}

bool TablaHash::eliminar(const std::string& clave) {
    int indice = funcionHash(clave);
    NodoHash* actual = tabla[indice];
    NodoHash* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->clave == clave) {
            if (anterior == nullptr) {
                // el nodo a eliminar es el primero de la lista
                tabla[indice] = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            tamanoActual--;
            return true; // eliminado
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false; // no se encontró
}

int TablaHash::obtenerTodasLasEstaciones(Estacion* arrEstaciones, int capacidadMaxima) const {
    int contador = 0;
    for (int i = 0; i < capacidad && contador < capacidadMaxima; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr && contador < capacidadMaxima) {
            arrEstaciones[contador] = actual->estacion;
            contador++;
            actual = actual->siguiente;
        }
    }
    return contador;
}

void TablaHash::ordenarYMostrarPorCapacidad() const {
    int n = tamanoActual;
    if (n == 0) {
        std::cout << "No hay estaciones cargadas.\n";
        return;
    }

    Estacion* arr = new Estacion[n];
    obtenerTodasLasEstaciones(arr, n);

    for (int i = 1; i < n; i++) {
        Estacion clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].getCapacidadAnclajes() > clave.getCapacidadAnclajes()) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = clave;
    }

    std::cout << "\nEstaciones Ordenadas por Capacidad\n";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i].getNombre()
                  << " | Capacidad: " << arr[i].getCapacidadAnclajes()
                  << " | Bicis: " << arr[i].getBicisDisponibles() << "\n";
    }

    delete[] arr;
}

void TablaHash::ordenarYMostrarPorBicisDisponibles() const {
     int n = tamanoActual;
    if (n == 0) {
        std::cout << "No hay estaciones cargadas.\n";
        return;
    }

    Estacion* arr = new Estacion[n];
    obtenerTodasLasEstaciones(arr, n);

    for (int i = 1; i < n; i++) {
        Estacion clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].getBicisDisponibles() > clave.getBicisDisponibles()) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = clave;
    }

    std::cout << "\nEstaciones Ordenadas por Bicis Disponibles\n";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i].getNombre()
                  << " | Bicis: " << arr[i].getBicisDisponibles()
                  << " | Capacidad: " << arr[i].getCapacidadAnclajes() << "\n";
    }

    delete[] arr;
}

void TablaHash::filtrarMenor20PorcientoOcupacion() const {
    int n = tamanoActual;
    if (n == 0) {
        std::cout << "No hay estaciones cargadas.\n";
        return;
    }

    Estacion* arr = new Estacion[n];
    obtenerTodasLasEstaciones(arr, n);

    std::cout << "\nEstaciones con menos del 20% de ocupacion\n";
    bool encontradas = false;
    for (int i = 0; i < n; i++) {
        double cap = static_cast<double>(arr[i].getCapacidadAnclajes());
        if (cap > 0) {
            double ocupacion = static_cast<double>(arr[i].getBicisDisponibles()) / cap;
            if (ocupacion < 0.20) {
                std::cout << arr[i].getNombre()
                          << " (Codigo: " << arr[i].getCodigo() << ")"
                          << " - ocupacion: " << (ocupacion * 100.0) << "%\n";
                encontradas = true;
            }
        }
    }
    if (!encontradas) std::cout << "No hay estaciones por debajo del 20%.\n";

    delete[] arr;
}