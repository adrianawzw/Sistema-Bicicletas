# Sistema de bicicletas

Aplicacion de consola en C++ para administrar estaciones y bicicletas, consultar recorridos por ciclovias y buscar combinaciones de estaciones para redistribuir bicicletas.

## Requisitos

- Compilador C++ con soporte para C++11 o posterior (por ejemplo, MinGW-w64/G++).
- Ejecutar el programa desde la carpeta del proyecto para que encuentre los archivos de datos.

## Compilacion y ejecucion

Desde PowerShell, ubicado en la carpeta del proyecto, compilar todos los modulos:

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic Main.cpp Sistema.cpp Estacion.cpp TablaHash.cpp GrafoCiclovias.cpp ColaBFS.cpp Bicicleta.cpp ArbolBicicletas.cpp Redistribuidor.cpp -o sistema.exe
```

Luego ejecutar:

```powershell
.\sistema.exe
```

No basta con compilar solo `Main.cpp` o el archivo activo: hay que incluir todos los archivos `.cpp` de la aplicacion para enlazar sus implementaciones.

## Modulos

- **`Main.cpp`**: punto de entrada. Carga los datos e inicia el menu principal.
- **`Sistema.h` / `Sistema.cpp`**: coordina los modulos, carga los archivos de datos y ofrece los menus de estaciones, bicicletas y redistribucion.
- **`Estacion.h` / `Estacion.cpp`**: define los datos de una estacion y sus accesores y modificadores.
- **`TablaHash.h` / `TablaHash.cpp`**: almacena estaciones indexadas por codigo en una tabla hash con encadenamiento de colisiones. Incluye busqueda, alta y baja, estadisticas, ordenamiento por insercion y filtro de ocupacion menor al 20%.
- **`NodoHash.h`**: nodo de las listas enlazadas que resuelven colisiones en la tabla hash.
- **`GrafoCiclovias.h` / `GrafoCiclovias.cpp`**: representa las conexiones entre estaciones mediante listas de adyacencia y busca recorridos minimos con BFS.
- **`ColaBFS.h` / `ColaBFS.cpp`**: implementa la cola usada por la busqueda BFS.
- **`Bicicleta.h` / `Bicicleta.cpp`**: representa una bicicleta, con codigo de estacion, tipo, estado y kilometraje.
- **`ArbolBicicletas.h` / `ArbolBicicletas.cpp`**: administra bicicletas en un arbol binario de busqueda ordenado por ID; permite insertar, buscar, listar, eliminar, contar averiadas y consultar la altura.
- **`NodoArbolBici.h`**: nodo del arbol de bicicletas.
- **`Redistribuidor.h` / `Redistribuidor.cpp`**: aplica backtracking para mostrar todos los subconjuntos de estaciones cuyos faltantes suman exactamente la capacidad del camion. Complejidad temporal en el peor caso: **O(2^n)**, con `n` estaciones.

## Archivos de datos

Los archivos se leen desde el directorio actual al iniciar el programa:

- **`estaciones.txt`**: una estacion por linea, con `codigo nombre barrio capacidad bicis_disponibles`.
- **`ciclovias.txt`**: una conexion por linea, con los codigos de las dos estaciones conectadas.
- **`bicicletas.txt`**: una bicicleta por linea, con `id codigo_estacion tipo estado kilometros`.

Los campos de texto se leen separados por espacios, por lo que codigos, nombres, barrios y tipos no deben contener espacios.

## Redistribucion

Desde el menu principal, elegir **Menu Redistribucion**. Ingresar la capacidad del camion, la cantidad de estaciones y, para cada una, su codigo y faltante (no negativo). El programa muestra todas las combinaciones que suman exactamente la capacidad; si no hay ninguna, lo informa.
