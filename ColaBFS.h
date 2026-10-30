#ifndef COLA_BFS_H
#define COLA_BFS_H

#include <string>

struct NodoCola {
    std::string codigoEstacion;
    int distancia;
    NodoCola* siguiente;

    NodoCola(std::string cod, int dist);
};

class ColaBFS {
private:
    NodoCola* frente;
    NodoCola* final;

public:
    ColaBFS();
    ~ColaBFS();

    bool estaVacia() const;
    void encolar(std::string cod, int dist);
    void desencolar(std::string& cod, int& dist);
};

#endif