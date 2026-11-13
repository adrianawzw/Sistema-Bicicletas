// Bicicleta.h
#ifndef BICICLETA_H
#define BICICLETA_H

#include <string>

class Bicicleta {
private:
    int biciId;
    std::string codigoEstacion;
    std::string tipo;    // "Mecanica" o "Electrica"
    std::string estado;  // "OK" o "Averiada"
    int kilometros;

public:
    Bicicleta();
    Bicicleta(int id, const std::string& codEstacion,
              const std::string& tipoBici, const std::string& estadoBici,
              int km);

    int getBiciId() const;
    const std::string& getCodigoEstacion() const;
    const std::string& getTipo() const;
    const std::string& getEstado() const;
    int getKilometros() const;

    bool estaAveriada() const;

    void setCodigoEstacion(const std::string& codEstacion);
    void setEstado(const std::string& estadoBici);
    void setKilometros(int km);

    void mostrar() const;
};

#endif
