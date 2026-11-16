#ifndef COLA_ESPERA_H
#define COLA_ESPERA_H

struct NodoEspera
{
    int dni;
    NodoEspera *siguiente;

    NodoEspera(int d) : dni(d), siguiente(nullptr) {}
};

class ColaEspera
{
    // Invariantes:
    //  - frente == nullptr <=> final == nullptr <=> cantidad == 0
    //  - si no esta vacia, final->siguiente == nullptr
    //  - no hay DNIs repetidos en la cola
private:
    NodoEspera *frente;
    NodoEspera *final;
    int cantidad;

    bool contiene(int dni) const;

public:
    ColaEspera();
    ~ColaEspera();

    // maneja memoria dinamica: no se permite copiar
    ColaEspera(const ColaEspera &) = delete;
    ColaEspera &operator=(const ColaEspera &) = delete;

    bool encolar(int dni);     // O(1) si no se valida; devuelve false si el DNI ya esta en cola
    bool desencolar(int &dni); // O(1); devuelve false si la cola esta vacia
    bool estaVacia() const;
    int getCantidad() const;
};

#endif