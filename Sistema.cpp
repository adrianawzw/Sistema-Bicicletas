#include "Sistema.h"
#include <iostream>
#include <fstream>
#include "Estacion.h"
#include <limits>

Sistema::Sistema() : tablaEstaciones(101) {
}

Sistema::~Sistema() {
}

void Sistema::cargarDatos() {
    std::ifstream archivo("estaciones.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error! No se pudo abrir estaciones.txt\n";
    } else {
        std::string codigo, nombre, barrio;
        int cap, bicis;
        int cargadas = 0;
        while (archivo >> codigo >> nombre >> barrio >> cap >> bicis) {
            if (tablaEstaciones.buscar(codigo) == nullptr) {
                Estacion nueva(codigo, nombre, barrio, cap, bicis);
                tablaEstaciones.insertar(codigo, nueva);
                cargadas++;
            }
        }
        archivo.close();
        std::cout << "Estaciones cargadas: " << cargadas << "\n";
    }

    grafoRed.cargarCicloviasDesdeArchivo("ciclovias.txt");
}

void Sistema::ejecutarMenu() {
    int opcion = 0;

    while (opcion != 9) {
        std::cout << "\nSISTEMA BICICLETAS\n";
        std::cout << "1. Mostrar estacion por codigo\n";
        std::cout << "2. Agregar estacion\n";
        std::cout << "3. Eliminar estacion\n";
        std::cout << "4. Ordenar por capacidad\n";
        std::cout << "5. Ordenar por bicis disponibles\n";
        std::cout << "6. Filtrar < 20% ocupacion\n";
        std::cout << "7. Camino minimo (BFS)\n";
        std::cout << "8. Estadisticas tabla hash\n";
        std::cout << "9. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {

            case 1: {
                std::string codigo;
                std::cout << "Codigo: ";
                std::cin >> codigo;
                Estacion* e = tablaEstaciones.buscar(codigo);
                if (e == nullptr) {
                    std::cout << "No existe esa estacion.\n";
                } else {
                    std::cout << "Codigo: " << e->getCodigo() << "\n";
                    std::cout << "Nombre: " << e->getNombre() << "\n";
                    std::cout << "Barrio: " << e->getBarrio() << "\n";
                    std::cout << "Capacidad: " << e->getCapacidadAnclajes() << "\n";
                    std::cout << "Bicis: " << e->getBicisDisponibles() << "\n";
                }
                break;
            }

            case 2: {
                std::string codigo, nombre, barrio;
                int cap, bicis;
                std::cout << "Codigo: "; std::cin >> codigo;
                if (tablaEstaciones.buscar(codigo) != nullptr) {
                    std::cout << "Ya existe esa estacion.\n";
                    break;
                }
                std::cout << "Nombre: "; std::cin >> nombre;
                std::cout << "Barrio: "; std::cin >> barrio;
                std::cout << "Capacidad: "; std::cin >> cap;
                std::cout << "Bicis: "; std::cin >> bicis;
                Estacion nueva(codigo, nombre, barrio, cap, bicis);
                tablaEstaciones.insertar(codigo, nueva);
                std::cout << "Estacion agregada!\n";
                break;
            }

            case 3: {
                std::string codigo;
                std::cout << "Codigo a eliminar: ";
                std::cin >> codigo;
                if (tablaEstaciones.eliminar(codigo))
                    std::cout << "Estacion eliminada!\n";
                else
                    std::cout << "No existe esa estacion\n";
                break;
            }

            case 4:
                tablaEstaciones.ordenarYMostrarPorCapacidad();
                break;

            case 5:
                tablaEstaciones.ordenarYMostrarPorBicisDisponibles();
                break;

            case 6:
                tablaEstaciones.filtrarMenor20PorcientoOcupacion();
                break;

            case 7: {
                std::string origen, destino;
                std::cout << "Origen: "; std::cin >> origen;
                std::cout << "Destino: "; std::cin >> destino;
                grafoRed.encontrarCaminoMasCorto(origen, destino);
                break;
            }

            case 8:
                std::cout << "Colisiones: " << tablaEstaciones.getColisiones() << "\n";
                std::cout << "Factor de carga: " << tablaEstaciones.getFactorCarga() << "\n";
                break;
            case 9:
                std::cout << "Saliendo...\n";
                break;

            default:
                std::cout << "Opcion invalida!\n";
        }
    }
}