#include "Sistema.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdio>
#include "Estacion.h"

// ---------------------------------------------------------------
// Lectura segura de la entrada (usada por el Menu Viajes, punto B)
// Invariante: todo numero ingresado es un entero valido.
// Rechaza letras, simbolos y cosas como "12abc", y evita que cin
// quede en estado de error (que provocaba un bucle infinito).
// ---------------------------------------------------------------
static int leerEntero(const std::string &mensaje)
{
    int valor;
    while (true)
    {
        std::cout << mensaje;
        if (std::cin >> valor)
        {
            // ignora espacios al final y acepta solo si la linea termina ahi
            while (std::cin.peek() == ' ' || std::cin.peek() == '\t')
                std::cin.get();
            int siguiente = std::cin.peek();
            if (siguiente == '\n' || siguiente == EOF)
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return valor;
            }
        }
        if (std::cin.eof())
            return 0; // fin de la entrada: evita un bucle infinito
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada invalida. Ingrese un numero entero.\n";
    }
}

// Invariante del DNI: numero de 7 u 8 digitos
static int leerDni()
{
    int dni;
    do
    {
        dni = leerEntero("DNI: ");
        if (std::cin.eof())
            return 0;
        if (dni < 1000000 || dni > 99999999)
            std::cout << "DNI invalido. Debe tener 7 u 8 digitos.\n";
    } while (dni < 1000000 || dni > 99999999);
    return dni;
}

Sistema::Sistema() : tablaEstaciones(101)
{
}

Sistema::~Sistema()
{
}

void Sistema::cargarDatos()
{
    std::ifstream archivo("estaciones.txt");
    if (!archivo.is_open())
    {
        std::cerr << "Error! No se pudo abrir estaciones.txt\n";
    }
    else
    {
        std::string codigo, nombre, barrio;
        int cap, bicis;
        int cargadas = 0;
        while (archivo >> codigo >> nombre >> barrio >> cap >> bicis)
        {
            if (tablaEstaciones.buscar(codigo) == nullptr)
            {
                Estacion nueva(codigo, nombre, barrio, cap, bicis);
                tablaEstaciones.insertar(codigo, nueva);
                cargadas++;
            }
        }
        archivo.close();
        std::cout << "Estaciones cargadas: " << cargadas << "\n";
    }

    grafoRed.cargarCicloviasDesdeArchivo("ciclovias.txt");

    // Cargar bicicletas desde archivo bicicletas.txt
    std::ifstream archivoBicis("bicicletas.txt");
    if (archivoBicis.is_open())
    {
        int id, km;
        std::string codEst, tipo, estado;
        int cargadasBicis = 0;

        while (archivoBicis >> id >> codEst >> tipo >> estado >> km)
        {
            Bicicleta b(id, codEst, tipo, estado, km);
            if (arbolBicis.insertar(b))
            {
                cargadasBicis++;
            }
        }
        archivoBicis.close();
        std::cout << "Bicicletas cargadas: " << cargadasBicis << "\n";
    }
    else
    {
        std::cerr << "Error! No se pudo abrir bicicletas.txt\n";
    }

    // cargar viajes
    listaViajes.cargarDesdeArchivo("viajes.txt");
}

// menu principal
void Sistema::ejecutarMenu()
{
    int opcion = -1;

    while (opcion != 0)
    {
        std::cout << "\nMENU PRINCIPAL\n";
        std::cout << "1. Menu Estaciones\n";
        std::cout << "2. Menu Bicicletas\n";
        std::cout << "3. Menu Redistribucion\n";
        std::cout << "4. Menu Viajes\n";
        std::cout << "0. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            menuEstaciones();
            break;

        case 2:
            menuBicicletas();
            break;

        case 3:
            menuRedistribucion();
            break;

        case 4:
            menuViajes();
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
void Sistema::menuEstaciones()
{
    int opcion = -1;

    while (opcion != 0)
    {
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

        switch (opcion)
        {
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
void Sistema::mostrarEstacion()
{
    std::string codigo;
    std::cout << "Codigo: ";
    std::cin >> codigo;
    Estacion *e = tablaEstaciones.buscar(codigo);
    if (e == nullptr)
    {
        std::cout << "No existe esa estacion.\n";
    }
    else
    {
        std::cout << "Codigo: " << e->getCodigo() << "\n";
        std::cout << "Nombre: " << e->getNombre() << "\n";
        std::cout << "Barrio: " << e->getBarrio() << "\n";
        std::cout << "Capacidad: " << e->getCapacidadAnclajes() << "\n";
        std::cout << "Bicis: " << e->getBicisDisponibles() << "\n";
    }
}

void Sistema::agregarEstacion()
{
    std::string codigo, nombre, barrio;
    int cap, bicis;
    std::cout << "Codigo: ";
    std::cin >> codigo;
    if (tablaEstaciones.buscar(codigo) != nullptr)
    {
        std::cout << "Ya existe esa estacion.\n";
        return;
    }
    std::cout << "Nombre: ";
    std::cin >> nombre;
    std::cout << "Barrio: ";
    std::cin >> barrio;
    std::cout << "Capacidad: ";
    std::cin >> cap;
    std::cout << "Bicis: ";
    std::cin >> bicis;
    Estacion nueva(codigo, nombre, barrio, cap, bicis);
    tablaEstaciones.insertar(codigo, nueva);
    std::cout << "Estacion agregada!\n";
}

void Sistema::eliminarEstacion()
{
    std::string codigo;
    std::cout << "Codigo a eliminar: ";
    std::cin >> codigo;
    if (tablaEstaciones.eliminar(codigo))
    {
        std::cout << "Estacion eliminada!\n";
    }
    else
    {
        std::cout << "No existe esa estacion\n";
    }
}

void Sistema::caminoMinimo()
{
    std::string origen, destino;
    std::cout << "Origen: ";
    std::cin >> origen;
    std::cout << "Destino: ";
    std::cin >> destino;
    grafoRed.encontrarCaminoMasCorto(origen, destino);
}

void Sistema::mostrarEstadisticasHash()
{
    std::cout << "Colisiones: " << tablaEstaciones.getColisiones() << "\n";
    std::cout << "Factor de carga: " << tablaEstaciones.getFactorCarga() << "\n";
}

// MENU BICICLETAS (arbol binario de busqueda)
void Sistema::menuBicicletas()
{
    int opcion = -1;

    while (opcion != 0)
    {
        std::cout << "\nMENU BICICLETAS (ABB)\n";
        std::cout << "1. Insertar bicicleta\n";
        std::cout << "2. Buscar por ID\n";
        std::cout << "3. Listar inorder (por ID)\n";
        std::cout << "4. Contar averiadas\n";
        std::cout << "5. Altura del arbol\n";
        std::cout << "6. Eliminar por ID\n";
        std::cout << "0. Volver al Menu Principal\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion)
        {
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

// ops menu bicicletas
void Sistema::insertarBicicleta()
{
    int id, km;
    std::string cod, tipo, estado;

    std::cout << "ID (numero): ";
    std::cin >> id;
    std::cout << "Estacion: ";
    std::cin >> cod;
    std::cout << "Tipo (Mecanica/Electrica): ";
    std::cin >> tipo;
    std::cout << "Estado (OK/Averiada): ";
    std::cin >> estado;
    std::cout << "Kilometros (numero): ";
    std::cin >> km;

    Bicicleta b(id, cod, tipo, estado, km);
    if (arbolBicis.insertar(b))
    {
        std::cout << "Bicicleta insertada.\n";
    }
    else
    {
        std::cout << "Ya existe una bicicleta con ese ID.\n";
    }
}

void Sistema::buscarBicicleta()
{
    int id;
    std::cout << "ID a buscar: ";
    std::cin >> id;

    const Bicicleta *b = arbolBicis.buscar(id);
    if (b != nullptr)
    {
        b->mostrar();
    }
    else
    {
        std::cout << "No existe esa bicicleta.\n";
    }
}

void Sistema::eliminarBicicleta()
{
    int id;
    std::cout << "ID a eliminar: ";
    std::cin >> id;

    if (arbolBicis.eliminar(id))
    {
        std::cout << "Bicicleta eliminada.\n";
    }
    else
    {
        std::cout << "No existe esa bicicleta.\n";
    }
}

// MENU VIAJES (modulo B)
void Sistema::menuViajes()
{
    int opcion = -1;

    while (opcion != 0)
    {
        std::cout << "\nMENU VIAJES\n";
        std::cout << "1. Cantidad de viajes por estacion y rango de fechas\n";
        std::cout << "2. Viajes de un usuario (DNI)\n";
        std::cout << "3. Bicicletas con mas de X km (enviar a revision)\n";
        std::cout << "4. Retirar bicicleta (cola de espera)\n";
        std::cout << "5. Devolver bicicleta\n";
        std::cout << "6. Enviar bicicleta averiada al taller\n";
        std::cout << "7. Extraer la bicicleta mas urgente del taller\n";
        std::cout << "0. Volver al Menu Principal\n";
        opcion = leerEntero("Opcion: ");

        switch (opcion)
        {
        case 1:
            contarViajesEstacion();
            break;

        case 2:
            buscarViajesUsuario();
            break;

        case 3:
            listarBicisMasDeKm();
            break;

        case 4:
            retirarBici();
            break;

        case 5:
            devolverBici();
            break;

        case 6:
            enviarATaller();
            break;

        case 7:
            atenderTaller();
            break;

        case 0:
            break;

        default:
            std::cout << "Opcion invalida!\n";
        }
    }
}

void Sistema::contarViajesEstacion()
{
    std::string codigo;
    std::cout << "Estacion de origen: ";
    std::cin >> codigo;
    int desde = leerEntero("Fecha desde (AAAAMMDD): ");
    int hasta = leerEntero("Fecha hasta (AAAAMMDD): ");
    int total = listaViajes.contarViajesPorEstacion(codigo, desde, hasta);
    std::cout << "Viajes encontrados: " << total << "\n";
}

void Sistema::buscarViajesUsuario()
{
    int dni = leerDni();
    int minutos = listaViajes.mostrarViajesPorUsuario(dni);
    std::cout << "Total de minutos pedaleados: " << minutos << "\n";
}

// B3: bicis con mas de X km, para enviarlas a revision
void Sistema::listarBicisMasDeKm()
{
    int x = leerEntero("Kilometros minimos (X): ");
    int total = arbolBicis.listarMasDeKm(x);
    if (total == 0)
    {
        std::cout << "No hay bicicletas con mas de " << x << " km.\n";
    }
    else
    {
        std::cout << "Bicicletas para revision: " << total << "\n";
    }
}

// B4: retirar una bici; si no hay disponibles, el usuario entra en la cola de espera
void Sistema::retirarBici()
{
    std::string codigo;
    std::cout << "Estacion: ";
    std::cin >> codigo;
    int dni = leerDni();

    Estacion *e = tablaEstaciones.buscar(codigo);
    if (e == nullptr)
    {
        std::cout << "No existe esa estacion.\n";
        return;
    }

    if (e->getBicisDisponibles() > 0)
    {
        e->setBicisDisponibles(e->getBicisDisponibles() - 1);
        std::cout << "Bicicleta retirada. Quedan " << e->getBicisDisponibles() << " disponibles.\n";
    }
    else
    {
        int posicion = gestorColas.encolarUsuario(codigo, dni);
        if (posicion == 0)
        {
            std::cout << "Ese DNI ya esta en la cola de espera de la estacion.\n";
        }
        else
        {
            std::cout << "No hay bicicletas disponibles. DNI " << dni
                      << " en cola de espera, posicion " << posicion << ".\n";
        }
    }
}

// B4: al devolver una bici, si hay cola se asigna al primero; si no, queda en la estacion
void Sistema::devolverBici()
{
    std::string codigo;
    std::cout << "Estacion donde se devuelve: ";
    std::cin >> codigo;

    Estacion *e = tablaEstaciones.buscar(codigo);
    if (e == nullptr)
    {
        std::cout << "No existe esa estacion.\n";
        return;
    }

    int dniAsignado;
    if (gestorColas.atenderSiguiente(codigo, dniAsignado))
    {
        std::cout << "Bicicleta asignada al DNI " << dniAsignado
                  << " (primero de la cola de espera).\n";
    }
    else if (e->getBicisDisponibles() >= e->getCapacidadAnclajes())
    {
        std::cout << "La estacion esta llena, no hay anclajes libres.\n";
    }
    else
    {
        e->setBicisDisponibles(e->getBicisDisponibles() + 1);
        std::cout << "Bicicleta devuelta. Ahora hay " << e->getBicisDisponibles() << " disponibles.\n";
    }
}

// B5: solo las bicis averiadas entran al taller; las electricas siempre con prioridad 1
void Sistema::enviarATaller()
{
    int id = leerEntero("ID de la bicicleta: ");

    const Bicicleta *b = arbolBicis.buscar(id);
    if (b == nullptr)
    {
        std::cout << "No existe esa bicicleta.\n";
        return;
    }
    if (!b->estaAveriada())
    {
        std::cout << "La bicicleta no esta averiada, no va al taller.\n";
        return;
    }

    int prioridad = 1;
    if (b->getTipo() != "Electrica")
    {
        do
        {
            prioridad = leerEntero("Prioridad (1 = mas urgente, 3 = menos urgente): ");
        } while ((prioridad < 1 || prioridad > 3) && !std::cin.eof());

        if (prioridad < 1 || prioridad > 3)
        {
            return; // fin de la entrada sin una prioridad valida
        }
    }
    else
    {
        std::cout << "Bicicleta electrica: prioridad 1 automatica.\n";
    }

    tallerReparaciones.insertar(id, prioridad);
    std::cout << "Bicicleta " << id << " enviada al taller con prioridad " << prioridad << ".\n";
}

// B5: extrae la bici mas urgente del taller
void Sistema::atenderTaller()
{
    ElementoTaller e;
    if (tallerReparaciones.extraerMasUrgente(e))
    {
        std::cout << "Sale del taller la bicicleta " << e.biciId
                  << " (prioridad " << e.prioridad << ").\n";
    }
    else
    {
        std::cout << "El taller no tiene bicicletas en espera.\n";
    }
}

// MENU Redistribucion
void Sistema::menuRedistribucion()
{
    int C;
    std::cout << "\nREDISTRIBUCION DE BICICLETAS\n";
    std::cout << "Ingrese la capacidad del camion: ";
    std::cin >> C;

    int n;
    std::cout << "Ingrese la cantidad de estaciones con faltante: ";
    std::cin >> n;

    if (n <= 0)
    {
        std::cout << "Cantidad invalida.\n";
        return;
    }

    FaltanteEstacion *estaciones = new FaltanteEstacion[n];

    for (int i = 0; i < n; i++)
    {
        std::cout << "Estacion " << (i + 1) << " - Codigo: ";
        std::cin >> estaciones[i].codigo;
        std::cout << "Estacion " << (i + 1) << " - Faltante: ";
        std::cin >> estaciones[i].faltante;
    }
    Redistribuidor redistribuidor(C);

    redistribuidor.buscarSubconjuntos(estaciones, n);

    // Limpiamos memoria
    delete[] estaciones;
}