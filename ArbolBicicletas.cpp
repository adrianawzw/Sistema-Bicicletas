// ArbolBicicletas.cpp
#include "ArbolBicicletas.h"
#include <iostream>

ArbolBicicletas::ArbolBicicletas() : raiz(nullptr), cantidadNodos(0) {}

ArbolBicicletas::~ArbolBicicletas() {
    liberarRec(raiz);   // postorder
    raiz = nullptr;
}

bool ArbolBicicletas::insertar(const Bicicleta& bici) {
    bool insertado = false;
    raiz = insertarRec(raiz, bici, insertado);
    if (insertado) {
        cantidadNodos++;
    }
    return insertado;
}

NodoArbolBici* ArbolBicicletas::insertarRec(NodoArbolBici* nodo,
                                            const Bicicleta& bici,
                                            bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoArbolBici(bici);
    }

    int idNuevo = bici.getBiciId();
    int idActual = nodo->dato.getBiciId();

    if (idNuevo < idActual) {
        nodo->izquierdo = insertarRec(nodo->izquierdo, bici, insertado);
    } else if (idNuevo > idActual) {
        nodo->derecho = insertarRec(nodo->derecho, bici, insertado);
    } else {
        insertado = false; // ID duplicado: no se inserta
    }
    return nodo;
}

NodoArbolBici* ArbolBicicletas::buscarRec(NodoArbolBici* nodo, int id) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    int idActual = nodo->dato.getBiciId();
    if (id == idActual) {
        return nodo;
    }
    if (id < idActual) {
        return buscarRec(nodo->izquierdo, id);
    }
    return buscarRec(nodo->derecho, id);
}

Bicicleta* ArbolBicicletas::buscar(int id) {
    NodoArbolBici* nodo = buscarRec(raiz, id);
    return (nodo != nullptr) ? &nodo->dato : nullptr;
}

const Bicicleta* ArbolBicicletas::buscar(int id) const {
    NodoArbolBici* nodo = buscarRec(raiz, id);
    return (nodo != nullptr) ? &nodo->dato : nullptr;
}

void ArbolBicicletas::inorderRec(NodoArbolBici* nodo) const {
    if (nodo == nullptr) {
        return;
    }
    inorderRec(nodo->izquierdo);
    nodo->dato.mostrar();
    inorderRec(nodo->derecho);
}

void ArbolBicicletas::listarInorder() const {
    if (raiz == nullptr) {
        std::cout << "No hay bicicletas cargadas.\n";
        return;
    }
    inorderRec(raiz);
}

int ArbolBicicletas::contarAveriadasRec(NodoArbolBici* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }
    int enEsteNodo = nodo->dato.estaAveriada() ? 1 : 0;
    return enEsteNodo
         + contarAveriadasRec(nodo->izquierdo)
         + contarAveriadasRec(nodo->derecho);
}

int ArbolBicicletas::contarAveriadas() const {
    return contarAveriadasRec(raiz);
}

int ArbolBicicletas::alturaRec(NodoArbolBici* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }
    int alturaIzq = alturaRec(nodo->izquierdo);
    int alturaDer = alturaRec(nodo->derecho);
    return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
}

int ArbolBicicletas::altura() const {
    return alturaRec(raiz);
}

void ArbolBicicletas::liberarRec(NodoArbolBici* nodo) {
    if (nodo == nullptr) {
        return;
    }
    liberarRec(nodo->izquierdo);
    liberarRec(nodo->derecho);
    delete nodo;   // postorder: primero hijos, después el nodo
}

NodoArbolBici* ArbolBicicletas::minimoNodo(NodoArbolBici* nodo) const {
    while (nodo != nullptr && nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

NodoArbolBici* ArbolBicicletas::eliminarRec(NodoArbolBici* nodo, int id,
                                            bool& eliminado) {
    if (nodo == nullptr) {
        return nullptr;
    }

    int idActual = nodo->dato.getBiciId();

    if (id < idActual) {
        nodo->izquierdo = eliminarRec(nodo->izquierdo, id, eliminado);
    } else if (id > idActual) {
        nodo->derecho = eliminarRec(nodo->derecho, id, eliminado);
    } else {
        eliminado = true;

        // Caso 1: nodo hoja o con solo hijo derecho
        if (nodo->izquierdo == nullptr) {
            NodoArbolBici* temp = nodo->derecho;
            delete nodo;
            return temp;
        }

        // Caso 2: nodo con solo hijo izquierdo
        if (nodo->derecho == nullptr) {
            NodoArbolBici* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }

        // Caso 3: dos hijos -> buscamos el sucesor inorder (mínimo del subárbol derecho)
        NodoArbolBici* sucesor = minimoNodo(nodo->derecho);
        nodo->dato = sucesor->dato;
        nodo->derecho = eliminarRec(nodo->derecho,
                                    sucesor->dato.getBiciId(),
                                    eliminado);
    }
    return nodo;
}

bool ArbolBicicletas::eliminar(int id) {
    bool eliminado = false;
    raiz = eliminarRec(raiz, id, eliminado);
    if (eliminado) {
        cantidadNodos--;
    }
    return eliminado;
}

bool ArbolBicicletas::estaVacio() const {
    return raiz == nullptr;
}

int ArbolBicicletas::getCantidad() const {
    return cantidadNodos;
}
