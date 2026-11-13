#include "Estacion.h"

// imp del constructor
Estacion::Estacion() {
    codigo = "";
    nombre = "";
    barrio = "";
    capacidadAnclajes = 0;
    bicisDisponibles = 0;
}

Estacion::Estacion(std::string cod, std::string nom, std::string bar, int cap, int bicis) {
    codigo = cod;
    nombre = nom;
    barrio = bar;

    // se ajustan los valores para que se cumpla el invariante
    if (cap < 0) cap = 0;
    capacidadAnclajes = cap;

    if (bicis < 0) bicis = 0;
    if (bicis > capacidadAnclajes) bicis = capacidadAnclajes;
    bicisDisponibles = bicis;
}

// metodos getter
std::string Estacion::getCodigo() const {
    return codigo;
}

std::string Estacion::getNombre() const {
    return nombre;
}

std::string Estacion::getBarrio() const {
    return barrio;
}

int Estacion::getCapacidadAnclajes() const {
    return capacidadAnclajes;
}

int Estacion::getBicisDisponibles() const {
    return bicisDisponibles;
}

// metodo setter: nunca deja la estacion fuera de [0, capacidadAnclajes]
void Estacion::setBicisDisponibles(int bicis) {
    if (bicis < 0) bicis = 0;
    if (bicis > capacidadAnclajes) bicis = capacidadAnclajes;
    bicisDisponibles = bicis;
}
