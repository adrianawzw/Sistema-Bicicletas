#ifndef REDISTRIBUIDOR_H
#define REDISTRIBUIDOR_H

#include <string>

struct FaltanteEstacion {
    std::string codigo;
    int faltante;
};

class Redistribuidor {
private:
    int capacidadCamion;

    // funcion recursiva de backtracking
    void buscarSubconjuntosRec(const FaltanteEstacion* estaciones, int n, 
                               int indice, int sumaActual,
                               int* seleccionados, int cantSeleccionados,
                               bool& encontrado) const;

public:
    Redistribuidor(int capacidad);

    void setCapacidadCamion(int capacidad);

    // funcion principal que llama el usuario
    void buscarSubconjuntos(const FaltanteEstacion* estaciones, int n) const;
};

#endif