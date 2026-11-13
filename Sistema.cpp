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

    //Cargar bicicletas desde archivo bicicletas.txt
    std::ifstream archivoBicis("bicicletas.txt");
    if (archivoBicis.is_open()) {
        int id, km;
        std::string codEst, tipo, estado;
        int cargadasBicis = 0;

        while (archivoBicis >> id >> codEst >> tipo >> estado >> km) {
            Bicicleta b(id, codEst, tipo, estado, km);
            if (arbolBicis.insertar(b)) {
            cargadasBicis++;
            }
        }
        archivoBicis.close();
        std::cout << "Bicicletas cargadas: " << cargadasBicis << "\n";
    } else {
    std::cerr << "Error! No se pudo abrir bicicletas.txt\n";
    }
}


void Sistema::ejecutarMenu() {
    int opcion = 0;

    while (opcion != 10) {                      // acá de debría decir Menú Principal y las funcionalidades de la tabla hash y el grafo deberían estar en un submenú "Menú Estaciones" y las funcionalidades del árbol de bicicletas en otro submenú "Menú Bicicletas"
        std::cout << "\nSISTEMA BICICLETAS\n"; // o un menú de estaciones y bicis junto (sección A)
        std::cout << "1. Mostrar estacion por codigo\n";
        std::cout << "2. Agregar estacion\n";
        std::cout << "3. Eliminar estacion\n";
        std::cout << "4. Ordenar por capacidad\n";
        std::cout << "5. Ordenar por bicis disponibles\n";
        std::cout << "6. Filtrar < 20% ocupacion\n";
        std::cout << "7. Camino minimo (BFS)\n";
        std::cout << "8. Estadisticas tabla hash\n";
        std::cout << "9. Menu bicicletas (seccion C)\n"; //Menu para el arbol de bicicletas
        std::cout << "10. Salir\n";

        // Validación de entrada para evitar errores si el usuario ingresa un valor no numérico
        std::cout << "Opcion: ";
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: Ingrese un numero valido.\n";
            continue; // Salta a la siguiente iteración del while
        }
        // Limpiar el buffer de entrada para evitar problemas con getline o futuras entradas
        std::cin.ignore(10000, '\n');

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
                menuBicicletas();
                break;
            case 10:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida!\n";
        }
    }
}

void Sistema::menuBicicletas() {
    int op = 0;
    while (op != 7) {
        std::cout << "\n--- BICICLETAS (ABB) ---\n";
        std::cout << "1. Insertar bicicleta\n";
        std::cout << "2. Buscar por ID\n";
        std::cout << "3. Listar inorder (por ID)\n";
        std::cout << "4. Contar averiadas\n";
        std::cout << "5. Altura del arbol\n";
        std::cout << "6. Eliminar por ID\n";
        std::cout << "7. Volver\n";
        std::cout << "Opcion: ";
        
        if (!(std::cin >> op)) {
            std::cin.clear(); 
            std::cin.ignore(10000, '\n');
            std::cout << "Error: Ingrese un numero valido.\n";
            continue;
        }
        // Limpiar el buffer de entrada para evitar problemas con getline o futuras entradas (en todo el menu)
        std::cin.ignore(10000, '\n'); // Limpieza del Enter
        
        switch (op) {
            case 1: {
                int id, km;
                std::string cod, tipo, estado;
                
                std::cout << "ID (numero): "; 
                if (!(std::cin >> id)) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "Error: El ID debe ser un numero.\n";
                    break;
                }
                std::cin.ignore(10000, '\n');
                
                std::cout << "Estacion: "; 
                std::cin >> cod;
                std::cin.ignore(10000, '\n');
                
                std::cout << "Tipo (Mecanica/Electrica): "; 
                std::cin >> tipo;
                std::cin.ignore(10000, '\n');
                
                std::cout << "Estado (OK/Averiada): "; 
                std::cin >> estado;
                std::cin.ignore(10000, '\n');
                
                std::cout << "Kilometros (numero): "; 
                if (!(std::cin >> km)) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "Error: Los km deben ser un numero.\n";
                    break;
                }
                std::cin.ignore(10000, '\n');

                Bicicleta b(id, cod, tipo, estado, km);
                if (arbolBicis.insertar(b)) {
                    std::cout << "Bicicleta insertada.\n";
                } else {
                    std::cout << "Ya existe una bicicleta con ese ID.\n";
                }
                break;
            }
            case 2: {
                int id;
                std::cout << "ID a buscar: "; 
                if (!(std::cin >> id)) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "Error: El ID debe ser un numero.\n";
                    break;
                }
                std::cin.ignore(10000, '\n');
                
                const Bicicleta* b = arbolBicis.buscar(id);
                if (b != nullptr) {
                    b->mostrar();
                } else {
                    std::cout << "No existe esa bicicleta.\n";
                }
                break;
            }
            case 3:
                arbolBicis.listarInorder();
                break;
            case 4:
                std::cout << "Bicicletas averiadas: " << arbolBicis.contarAveriadas() << "\n";
                break;
            case 5:
                std::cout << "Altura del arbol: " << arbolBicis.altura() << "\n";
                break;
            case 6: {
                int id;
                std::cout << "ID a eliminar: "; 
                if (!(std::cin >> id)) {
                    std::cin.clear(); std::cin.ignore(10000, '\n');
                    std::cout << "Error: El ID debe ser un numero.\n";
                    break;
                }
                std::cin.ignore(10000, '\n');
                
                if (arbolBicis.eliminar(id)) {
                    std::cout << "Bicicleta eliminada.\n";
                } else {
                    std::cout << "No existe esa bicicleta.\n";
                }
                break;
            }
            case 7:
                std::cout << "Volviendo...\n";
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }
    }
}