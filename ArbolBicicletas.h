// ArbolBicicletas.h
#ifndef ARBOL_BICICLETAS_H
#define ARBOL_BICICLETAS_H

#include "NodoArbolBici.h"
#include "Bicicleta.h"

class ArbolBicicletas
{
private:
    NodoArbolBici *raiz;
    int cantidadNodos;

    // Funciones recursivas privadas
    NodoArbolBici *insertarRec(NodoArbolBici *nodo, const Bicicleta &bici, bool &insertado);
    NodoArbolBici *buscarRec(NodoArbolBici *nodo, int id) const;
    void inorderRec(NodoArbolBici *nodo) const;
    int contarAveriadasRec(NodoArbolBici *nodo) const;
    int alturaRec(NodoArbolBici *nodo) const;
    void liberarRec(NodoArbolBici *nodo);
    NodoArbolBici *eliminarRec(NodoArbolBici *nodo, int id, bool &eliminado);
    // Función auxiliar para encontrar el nodo con el valor mínimo en un subárbol
    NodoArbolBici *minimoNodo(NodoArbolBici *nodo) const;
    int listarMasDeKmRec(NodoArbolBici *nodo, int x) const; // NUEVO (B3)

public:
    ArbolBicicletas();
    ~ArbolBicicletas();

    // Evitar copias accidentales del árbol 
    ArbolBicicletas(const ArbolBicicletas &) = delete;
    ArbolBicicletas &operator=(const ArbolBicicletas &) = delete;

    // Funciones públicas
    bool insertar(const Bicicleta &bici);
    Bicicleta *buscar(int id);
    const Bicicleta *buscar(int id) const;

    void listarInorder() const;
    int contarAveriadas() const;
    int listarMasDeKm(int x) const; // NUEVO (B3): lista las bicis con mas de x km y devuelve cuantas
    int altura() const;
    bool eliminar(int id);

    bool estaVacio() const;
    int getCantidad() const;
};

#endif
