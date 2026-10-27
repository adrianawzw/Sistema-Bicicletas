#include "Estacion.h"

// imp del constructor
Estacion::Estacion(std::string cod, std::string nom, std::string bar, int cap, int bicis) {
    codigo = cod;
    nombre = nom;
    barrio = bar;
    capacidadAnclajes = cap;
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

// metodo setter
void Estacion::setBicisDisponibles(int bicis) {
    bicisDisponibles = bicis;
}