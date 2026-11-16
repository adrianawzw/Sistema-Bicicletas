#include "Viaje.h"
#include <iostream>

Viaje::Viaje() : viajeId(0), biciId(0), dniUsuario(0), estacionOrigen(""),
                 estacionDestino(""), fecha(0), duracionMin(0) {}

Viaje::Viaje(int id, int bici, int dni, std::string origen, std::string destino, int fec, int dur)
    : viajeId(id), biciId(bici), dniUsuario(dni), estacionOrigen(origen),
      estacionDestino(destino), fecha(0), duracionMin(0)
{
    // se ajustan los valores para que se cumpla el invariante
    if (dur >= 0)
        duracionMin = dur;

    int anio = fec / 10000;
    int mes = (fec / 100) % 100;
    int dia = fec % 100;
    if (anio > 0 && mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31)
    {
        fecha = fec;
    }
}

int Viaje::getViajeId() const { return viajeId; }
int Viaje::getBiciId() const { return biciId; }
int Viaje::getDniUsuario() const { return dniUsuario; }
std::string Viaje::getEstacionOrigen() const { return estacionOrigen; }
std::string Viaje::getEstacionDestino() const { return estacionDestino; }
int Viaje::getFecha() const { return fecha; }
int Viaje::getDuracionMin() const { return duracionMin; }

void Viaje::mostrar() const
{
    std::cout << "Viaje " << viajeId
              << " | Bici: " << biciId
              << " | " << estacionOrigen << " -> " << estacionDestino
              << " | Fecha: " << fecha
              << " | " << duracionMin << " min\n";
}