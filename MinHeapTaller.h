#ifndef MIN_HEAP_TALLER_H
#define MIN_HEAP_TALLER_H

struct ElementoTaller
{
    int biciId;
    int prioridad; // 1 (mas urgente) a 3
    int orden;     // orden de llegada, desempata prioridades iguales
};

class MinHeapTaller
{
    // Invariantes:
    //  - 1 <= prioridad <= 3 en todo elemento
    //  - heap minimo: el padre es mas urgente o igual que sus hijos
    //  - 0 <= tamano <= capacidad
private:
    ElementoTaller *datos;
    int tamano;
    int capacidad;
    int contadorOrden;

    bool esMasUrgente(const ElementoTaller &a, const ElementoTaller &b) const;
    void subir(int i);
    void bajar(int i);
    void duplicarCapacidad();

public:
    MinHeapTaller();
    ~MinHeapTaller();

    // maneja memoria dinamica: no se permite copiar
    MinHeapTaller(const MinHeapTaller &) = delete;
    MinHeapTaller &operator=(const MinHeapTaller &) = delete;

    bool insertar(int biciId, int prioridad);          // O(log n); false si la prioridad es invalida
    bool extraerMasUrgente(ElementoTaller &resultado); // O(log n); false si el taller esta vacio
    bool estaVacio() const;
    int getTamano() const;
};

#endif