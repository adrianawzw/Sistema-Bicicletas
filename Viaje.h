#ifndef VIAJE_H
#define VIAJE_H

#include <string>

class Viaje
{
private:
    int viajeId;
    int biciId;
    int dniUsuario;
    std::string estacionOrigen;
    std::string estacionDestino;
    int fecha; // AAAAMMDD
    int duracionMin;

public:
    Viaje();
    Viaje(int id, int bici, int dni, std::string origen, std::string destino, int fec, int dur);

    int getViajeId() const;
    int getBiciId() const;
    int getDniUsuario() const;
    std::string getEstacionOrigen() const;
    std::string getEstacionDestino() const;
    int getFecha() const;
    int getDuracionMin() const;

    void mostrar() const;
};

#endif