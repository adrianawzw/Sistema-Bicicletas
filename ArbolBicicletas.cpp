// ArbolBicicletas.cpp
#include "ArbolBicicletas.h"
#include <iostream>

// Constructor que inicializa el árbol vacío y la cantidad de nodos en 0
ArbolBicicletas::ArbolBicicletas() : raiz(nullptr), cantidadNodos(0) {}

// Declaramos el destructor para que se llame automáticamente al finalizar el programa y así liberar la memoria de todos los nodos del árbol.
ArbolBicicletas::~ArbolBicicletas()
{
    liberarRec(raiz); // postorder
    raiz = nullptr;
}


// Inserta una bicicleta en el árbol. Devuelve true si se insertó, false si ya existía.
bool ArbolBicicletas::insertar(const Bicicleta &bici)
{
    bool insertado = false;
    raiz = insertarRec(raiz, bici, insertado);
    if (insertado)
    {
        cantidadNodos++; //suma nodo
    }
    return insertado;
}

// Busca una bicicleta por su ID. Devuelve un puntero a la bicicleta si se encuentra, nullptr si no.
// *nodo es el nodo actual en la recursión, y *id* es el ID de la bicicleta que se busca
NodoArbolBici *ArbolBicicletas::insertarRec(NodoArbolBici *nodo,
                                            const Bicicleta &bici,
                                            bool &insertado)
{       
    //Cuando llega a un espacio vacío, crea un puntero a un nuevo nodo con la bicicleta
    if (nodo == nullptr)
    {
        insertado = true;
        return new NodoArbolBici(bici); // crea un nuevo nodo con la bicicleta
    }

    int idNuevo = bici.getBiciId(); // ID de la bicicleta a insertar 
    int idActual = nodo->dato.getBiciId(); // ID del nodo actual por el que se está recorriendo el árbol con el fin de encontrar el lugar correcto para insertar la nueva bicicleta.
    
    // Comparación de IDs para decidir la dirección de inserción. Objetivo: mantener el orden del árbol binario de búsqueda.
    if (idNuevo < idActual)
    {
        nodo->izquierdo = insertarRec(nodo->izquierdo, bici, insertado);
    }
    else if (idNuevo > idActual)
    {
        nodo->derecho = insertarRec(nodo->derecho, bici, insertado);
    }
    else
    {
        insertado = false; // ID duplicado: no se inserta
    }
    return nodo;
}


// Función recursiva para buscar una bicicleta por su ID
NodoArbolBici *ArbolBicicletas::buscarRec(NodoArbolBici *nodo, int id) const
{
    if (nodo == nullptr)
    {
        return nullptr;
    }

    int idActual = nodo->dato.getBiciId();
    if (id == idActual)
    {
        return nodo;
    }
    if (id < idActual)
    {
        return buscarRec(nodo->izquierdo, id);
    }
    return buscarRec(nodo->derecho, id); // Continúa buscando en el subárbol derecho
}

// Función pública para buscar una bicicleta por su ID
Bicicleta *ArbolBicicletas::buscar(int id)
{
    NodoArbolBici *nodo = buscarRec(raiz, id);
    return (nodo != nullptr) ? &nodo->dato : nullptr; // Devuelve un puntero a la bicicleta si se encuentra, nullptr si no
}

// Es una medida de seguridad. Garantiza que quien reciba ese puntero solo pueda leer la bici (no modificarla) y que la función buscar no altere el árbol.
const Bicicleta *ArbolBicicletas::buscar(int id) const
{
    NodoArbolBici *nodo = buscarRec(raiz, id);
    return (nodo != nullptr) ? &nodo->dato : nullptr;
}

// Función recursiva para recorrer el árbol en orden (inorder) y mostrar las bicicletas
void ArbolBicicletas::inorderRec(NodoArbolBici *nodo) const
{
    if (nodo == nullptr)
    {
        return;
    }
    inorderRec(nodo->izquierdo); // Primero recorre el subárbol izquierdo
    nodo->dato.mostrar(); // Luego muestra la bicicleta del nodo actual
    inorderRec(nodo->derecho); // Finalmente recorre el subárbol derecho
}

void ArbolBicicletas::listarInorder() const
{
    if (raiz == nullptr)
    {
        std::cout << "No hay bicicletas cargadas.\n";
        return;
    }
    inorderRec(raiz);
}



int ArbolBicicletas::contarAveriadasRec(NodoArbolBici *nodo) const
{   //con preorder
    if (nodo == nullptr)
    {
        return 0; // Caso base: si el nodo es nulo, no hay bicicletas averiadas en este subárbol
    }
    int enEsteNodo = nodo->dato.estaAveriada() ? 1 : 0; // Cuenta 1 si la bicicleta en este nodo está averiada, 0 si no
    return enEsteNodo + contarAveriadasRec(nodo->izquierdo) + contarAveriadasRec(nodo->derecho); // Suma la cuenta de este nodo con las cuentas de los subárboles izquierdo y derecho
}
// Función pública para contar cuántas bicicletas están averiadas en el árbol
int ArbolBicicletas::contarAveriadas() const
{
    return contarAveriadasRec(raiz);
}

int ArbolBicicletas::alturaRec(NodoArbolBici *nodo) const
{
    if (nodo == nullptr)
    {
        return 0; // la altura es 0
    }
    int alturaIzq = alturaRec(nodo->izquierdo); 
    int alturaDer = alturaRec(nodo->derecho);
    return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer); //toma la altura mayor
}
// Función pública para obtener la altura del árbol
int ArbolBicicletas::altura() const
{
    return alturaRec(raiz);
}

// Función recursiva para liberar la memoria de todos los nodos del árbol
// como usamos new() para crear nodos, debemos usar delete para liberar la memoria y evitar fugas de memoria
void ArbolBicicletas::liberarRec(NodoArbolBici *nodo)
{
    if (nodo == nullptr)
    {
        return;
    }
    liberarRec(nodo->izquierdo);
    liberarRec(nodo->derecho);
    delete nodo; // postorder: primero hijos, después el nodo actual
}


//punto extra

// Es necesario para eliminar un nodo con dos hijos.
// Encuentra el nodo con el valor mínimo en un subárbol dado. Se utiliza para encontrar el sucesor inorder al eliminar un nodo con dos hijos.
NodoArbolBici *ArbolBicicletas::minimoNodo(NodoArbolBici *nodo) const
{
    while (nodo != nullptr && nodo->izquierdo != nullptr)
    {
        nodo = nodo->izquierdo;
    }
    return nodo;
}


NodoArbolBici *ArbolBicicletas::eliminarRec(NodoArbolBici *nodo, int id,
                                            bool &eliminado)
{
    if (nodo == nullptr)
    {
        return nullptr; // no se encontró el nodo a eliminar
    }

    int idActual = nodo->dato.getBiciId();

    if (id < idActual)
    {
        nodo->izquierdo = eliminarRec(nodo->izquierdo, id, eliminado);
    }
    else if (id > idActual)
    {
        nodo->derecho = eliminarRec(nodo->derecho, id, eliminado);
    }
    else
    {   //mantener camino 
        eliminado = true; // nodo encontrado, se eliminará

        // Caso 1: nodo hoja o con solo hijo derecho
        if (nodo->izquierdo == nullptr) 
        {
            NodoArbolBici *temp = nodo->derecho; //temporal apunta al hijo derecho
            delete nodo;
            return temp;
        }

        // Caso 2: nodo con solo hijo izquierdo
        if (nodo->derecho == nullptr)
        {
            NodoArbolBici *temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }

        // Caso 3: dos hijos -> buscamos el sucesor inorder (mínimo del subárbol derecho)
        NodoArbolBici *sucesor = minimoNodo(nodo->derecho); //empiezo por lo más pequeño del subárbol derecho
        nodo->dato = sucesor->dato; //sucesor es el que reemplaza al nodo a eliminar para mantener el orden del árbol 
        nodo->derecho = eliminarRec(nodo->derecho,
                                    sucesor->dato.getBiciId(),
                                    eliminado); // eliminamos el sucesor que ahora está duplicado
    }
    return nodo;
}
// Función pública para eliminar una bicicleta por su ID
bool ArbolBicicletas::eliminar(int id)
{
    bool eliminado = false;
    raiz = eliminarRec(raiz, id, eliminado);
    if (eliminado)
    {
        cantidadNodos--;
    }
    return eliminado;
}

bool ArbolBicicletas::estaVacio() const
{
    return raiz == nullptr;
}

int ArbolBicicletas::getCantidad() const
{
    return cantidadNodos;
}




// NUEVO (B3): inorder, muestra las bicis con kilometros > x (quedan ordenadas por ID)
int ArbolBicicletas::listarMasDeKmRec(NodoArbolBici *nodo, int x) const
{
    if (nodo == nullptr)
    {
        return 0;
    }
    int cantidad = listarMasDeKmRec(nodo->izquierdo, x);
    if (nodo->dato.getKilometros() > x)
    {
        nodo->dato.mostrar();
        cantidad++;
    }
    cantidad += listarMasDeKmRec(nodo->derecho, x);
    return cantidad;
}

int ArbolBicicletas::listarMasDeKm(int x) const
{
    return listarMasDeKmRec(raiz, x);
}