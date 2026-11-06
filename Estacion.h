#ifndef ESTACION_H
#define ESTACION_H

#include <string>

class Estacion {
private:
    std::string codigo;
    std::string nombre;
    std::string barrio;
    int capacidadAnclajes;
    int bicisDisponibles;

public:
    Estacion();
    // Constructor
    Estacion(std::string cod, std::string nom, std::string bar, int cap, int bicis);

    // Getters
    std::string getCodigo() const;
    std::string getNombre() const;
    std::string getBarrio() const;
    int getCapacidadAnclajes() const;
    int getBicisDisponibles() const;

    // Setters
    void setBicisDisponibles(int bicis);
};

#endif