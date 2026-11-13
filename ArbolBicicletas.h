// ArbolBicicletas.h
#ifndef ARBOL_BICICLETAS_H
#define ARBOL_BICICLETAS_H

#include "NodoArbolBici.h"
#include "Bicicleta.h"

class ArbolBicicletas {
private:
    NodoArbolBici* raiz;
    int cantidadNodos;

    NodoArbolBici* insertarRec(NodoArbolBici* nodo, const Bicicleta& bici, bool& insertado);
    NodoArbolBici* buscarRec(NodoArbolBici* nodo, int id) const;
    void inorderRec(NodoArbolBici* nodo) const;
    int contarAveriadasRec(NodoArbolBici* nodo) const;
    int alturaRec(NodoArbolBici* nodo) const;
    void liberarRec(NodoArbolBici* nodo);
    NodoArbolBici* eliminarRec(NodoArbolBici* nodo, int id, bool& eliminado);
    NodoArbolBici* minimoNodo(NodoArbolBici* nodo) const;

public:
    ArbolBicicletas();
    ~ArbolBicicletas();

    // Evitamos copias accidentales del árbol
    ArbolBicicletas(const ArbolBicicletas&) = delete;
    ArbolBicicletas& operator=(const ArbolBicicletas&) = delete;

    bool insertar(const Bicicleta& bici);
    Bicicleta* buscar(int id);
    const Bicicleta* buscar(int id) const;

    void listarInorder() const;
    int contarAveriadas() const;
    int altura() const;
    bool eliminar(int id);

    bool estaVacio() const;
    int getCantidad() const;
};

#endif
