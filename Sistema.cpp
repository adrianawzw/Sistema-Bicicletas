#include "Sistema.h"
#include <iostream>
#include <fstream>
#include "Estacion.h"

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

// menu principal
void Sistema::ejecutarMenu() {
    int opcion = -1;

    while (opcion != 0) {
        std::cout << "\nMENU PRINCIPAL\n";
        std::cout << "1. Menu Estaciones\n";
        std::cout << "2. Menu Bicicletas\n";
        std::cout << "3. Menu Redistribucion\n"; 
        std::cout << "0. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                menuEstaciones();
                break;

            case 2:
                menuBicicletas();
                break;

            case 3:
                menuRedistribucion();
                break;

            case 0:
                std::cout << "Saliendo...\n";
                break;

            default:
                std::cout << "Opcion invalida!\n";
        }
    }
}

// MENU ESTACIONES (tabla hash + grafo de ciclovias)
void Sistema::menuEstaciones() {
    int opcion = -1;

    while (opcion != 0) {
        std::cout << "\nMENU ESTACIONES\n";
        std::cout << "1. Mostrar estacion por codigo\n";
        std::cout << "2. Agregar estacion\n";
        std::cout << "3. Eliminar estacion\n";
        std::cout << "4. Ordenar por capacidad\n";
        std::cout << "5. Ordenar por bicis disponibles\n";
        std::cout << "6. Filtrar < 20% ocupacion\n";
        std::cout << "7. Camino minimo (BFS)\n";
        std::cout << "8. Estadisticas tabla hash\n";
        std::cout << "0. Volver al Menu Principal\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarEstacion();
                break;

            case 2:
                agregarEstacion();
                break;

            case 3:
                eliminarEstacion();
                break;

            case 4:
                tablaEstaciones.ordenarYMostrarPorCapacidad();
                break;

            case 5:
                tablaEstaciones.ordenarYMostrarPorBicisDisponibles();
                break;

            case 6:
                tablaEstaciones.filtrarMenor20PorcientoOcupacion();
                break;

            case 7:
                caminoMinimo();
                break;

            case 8:
                mostrarEstadisticasHash();
                break;

            case 0:
                break;
            default:
                std::cout << "Opcion invalida!\n";
        }
    }
}

// ops menu estaciones
void Sistema::mostrarEstacion() {
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
}

void Sistema::agregarEstacion() {
    std::string codigo, nombre, barrio;
    int cap, bicis;
    std::cout << "Codigo: "; std::cin >> codigo;
    if (tablaEstaciones.buscar(codigo) != nullptr) {
        std::cout << "Ya existe esa estacion.\n";
        return;
    }
    std::cout << "Nombre: "; std::cin >> nombre;
    std::cout << "Barrio: "; std::cin >> barrio;
    std::cout << "Capacidad: "; std::cin >> cap;
    std::cout << "Bicis: "; std::cin >> bicis;
    Estacion nueva(codigo, nombre, barrio, cap, bicis);
    tablaEstaciones.insertar(codigo, nueva);
    std::cout << "Estacion agregada!\n";
}

void Sistema::eliminarEstacion() {
    std::string codigo;
    std::cout << "Codigo a eliminar: ";
    std::cin >> codigo;
    if (tablaEstaciones.eliminar(codigo)) {
        std::cout << "Estacion eliminada!\n";
    } else {
        std::cout << "No existe esa estacion\n";
    }
}

void Sistema::caminoMinimo() {
    std::string origen, destino;
    std::cout << "Origen: "; std::cin >> origen;
    std::cout << "Destino: "; std::cin >> destino;
    grafoRed.encontrarCaminoMasCorto(origen, destino);
}

void Sistema::mostrarEstadisticasHash() {
    std::cout << "Colisiones: " << tablaEstaciones.getColisiones() << "\n";
    std::cout << "Factor de carga: " << tablaEstaciones.getFactorCarga() << "\n";
}

// MENU BICICLETAS (arbol binario de busqueda)
void Sistema::menuBicicletas() {
    int opcion = -1;

    while (opcion != 0) {
        std::cout << "\nMENU BICICLETAS (ABB)\n";
        std::cout << "1. Insertar bicicleta\n";
        std::cout << "2. Buscar por ID\n";
        std::cout << "3. Listar inorder (por ID)\n";
        std::cout << "4. Contar averiadas\n";
        std::cout << "5. Altura del arbol\n";
        std::cout << "6. Eliminar por ID\n";
        std::cout << "0. Volver al Menu Principal\n";
        std::cout << "Opcion: ";
        // Validación de entrada para evitar errores al ingresar letras
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: Ingrese un numero valido.\n";
            opcion = -1; // Reiniciamos la opción para que el bucle continúe
            continue; // Vuelve a pedir la opcion
        }
        std::cin.ignore(10000, '\n');

        switch (opcion) {
            case 1:
                insertarBicicleta();
                break;

            case 2:
                buscarBicicleta();
                break;

            case 3:
                arbolBicis.listarInorder();
                break;

            case 4:
                std::cout << "Bicicletas averiadas: " << arbolBicis.contarAveriadas() << "\n";
                break;

            case 5:
                std::cout << "Altura del arbol: " << arbolBicis.altura() << "\n";
                break;

            case 6:
                eliminarBicicleta();
                break;

            case 0:
                break;

            default:
                std::cout << "Opcion invalida!\n";
        }
    }
}


// ops menu bicicletas areglado con invariantes
void Sistema::insertarBicicleta() {
    int id, km;
    std::string cod, tipo, estado;

    std::cout << "ID (numero): "; 
    if (!(std::cin >> id)) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        std::cout << "Error: El ID debe ser un numero.\n";
        return;
    }
    std::cin.ignore(10000, '\n');

    std::cout << "Estacion: "; std::cin >> cod;
    std::cout << "Tipo (Mecanica/Electrica): "; std::cin >> tipo;
    std::cout << "Estado (OK/Averiada): "; std::cin >> estado;
    
    std::cout << "Kilometros (numero): "; 
    if (!(std::cin >> km)) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        std::cout << "Error: Los km deben ser un numero.\n";
        return;
    }
    std::cin.ignore(10000, '\n');

    Bicicleta b(id, cod, tipo, estado, km);
    if (arbolBicis.insertar(b)) {
        std::cout << "Bicicleta insertada.\n";
    } else {
        std::cout << "Ya existe una bicicleta con ese ID.\n";
    }
}

void Sistema::buscarBicicleta() {
    int id;
    std::cout << "ID a buscar: "; 
    if (!(std::cin >> id)) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        std::cout << "Error: El ID debe ser un numero.\n";
        return;
    }
    std::cin.ignore(10000, '\n');

    const Bicicleta* b = arbolBicis.buscar(id);
    if (b != nullptr) {
        b->mostrar();
    } else {
        std::cout << "No existe esa bicicleta.\n";
    }
}

void Sistema::eliminarBicicleta() {
    int id;
    std::cout << "ID a eliminar: "; 
    if (!(std::cin >> id)) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        std::cout << "Error: El ID debe ser un numero.\n";
        return;
    }
    std::cin.ignore(10000, '\n');

    if (arbolBicis.eliminar(id)) {
        std::cout << "Bicicleta eliminada.\n";
    } else {
        std::cout << "No existe esa bicicleta.\n";
    }
}

// MENU Redistribucion 
void Sistema::menuRedistribucion() {
    int C;
    std::cout << "\nREDISTRIBUCION DE BICICLETAS\n";
    std::cout << "Ingrese la capacidad del camion: ";
    std::cin >> C;

    int n;
    std::cout << "Ingrese la cantidad de estaciones con faltante: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Cantidad invalida.\n";
        return;
    }

    FaltanteEstacion* estaciones = new FaltanteEstacion[n];
    
    for (int i = 0; i < n; i++) {
        std::cout << "Estacion " << (i + 1) << " - Codigo: ";
        std::cin >> estaciones[i].codigo;

        // --- VALIDACIÓN DEL INVARIANTE ---
        do {
            std::cout << "Estacion " << (i + 1) << " - Faltante (debe ser >= 0): ";
            std::cin >> estaciones[i].faltante;
            if (estaciones[i].faltante < 0) {
                std::cout << "Error: El faltante no puede ser negativo.\n";
            }
        } while (estaciones[i].faltante < 0);
        // ---------------------------------
        
    }
    Redistribuidor redistribuidor(C);
    
    redistribuidor.buscarSubconjuntos(estaciones, n);

    // Limpiamos memoria
    delete[] estaciones;
}