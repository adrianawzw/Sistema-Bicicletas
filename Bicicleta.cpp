// Bicicleta.cpp
#include "Bicicleta.h"
#include <iostream>

// Constructor por defecto: le ponemos valores válidos por defecto
Bicicleta::Bicicleta()
    : biciId(0), codigoEstacion(""), tipo("Mecanica"), estado("OK"), kilometros(0) {}

// Constructor con parámetros
Bicicleta::Bicicleta(int id, const std::string& codEstacion,
                     const std::string& tipoBici, const std::string& estadoBici,
                     int km) {
    
    // valores directos
    biciId = id;
    codigoEstacion = codEstacion;
    kilometros = km;

    // --- INVARIANTES ---
    // kilometros >= 0 (antes solo lo controlaba el setter, el constructor no)
    kilometros = (km < 0) ? 0 : km;
    if (tipoBici != "Mecanica" && tipoBici != "Electrica") {
        tipo = "Mecanica";
    } else {
        tipo = tipoBici;
    }

    if (estadoBici != "OK" && estadoBici != "Averiada") {
        estado = "Averiada"; 
    } else {
        estado = estadoBici;
    }
    // -------------------
}

int Bicicleta::getBiciId() const { return biciId; }
const std::string& Bicicleta::getCodigoEstacion() const { return codigoEstacion; }
const std::string& Bicicleta::getTipo() const { return tipo; }
const std::string& Bicicleta::getEstado() const { return estado; }
int Bicicleta::getKilometros() const { return kilometros; }

bool Bicicleta::estaAveriada() const {
    return estado == "Averiada";
}

void Bicicleta::setCodigoEstacion(const std::string& codEstacion) {
    // Invariante: el código de estación no puede estar vacío
    if (!codEstacion.empty()) {
        codigoEstacion = codEstacion;
    }
}

void Bicicleta::setEstado(const std::string& estadoBici) {
    // Invariante: solo acepta "OK" o "Averiada"
    if (estadoBici == "OK" || estadoBici == "Averiada") {
        estado = estadoBici;
    }
}

void Bicicleta::setKilometros(int km) {
    // Invariante: los kilómetros no pueden ser negativos
    if (km >= 0) {
        kilometros = km;
    }
}

void Bicicleta::mostrar() const {
    std::cout << "ID: " << biciId
              << " | Estacion: " << codigoEstacion
              << " | Tipo: " << tipo
              << " | Estado: " << estado
              << " | Km: " << kilometros << "\n";
}