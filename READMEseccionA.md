### Módulo A: Gestión de Estaciones

Este módulo permite dar de alta, baja y modificar estaciones, así como también buscar caminos mínimos entre ellas.

**Estructuras utilizadas:**
* Tabla de Hash con encadenamiento
* Grafo con listas de adyacencia
* Cola simple y búsqueda BFS

**Análisis de rendimiento:**

* **Inserción, búsqueda y eliminación en Tabla Hash:**
  * *Complejidad:* `O(1)` en promedio, `O(n)` en el peor caso.
  * *Justificación:* La tabla hash permite acceso casi directo a los datos. El peor caso ocurre si todas las estaciones caen en el mismo casillero (colisión) y se degenera en una búsqueda lineal en la lista enlazada.

* **Ordenamiento por capacidad / bicis:**
  * *Complejidad:* `O(n²)`.
  * *Justificación:* Se utilizó el algoritmo de Inserción sobre un arreglo auxiliar. Es eficiente para conjuntos de datos pequeños o casi ordenados.

* **Filtro < 20% de ocupación:**
  * *Complejidad:* `O(n)`.
  * *Justificación:* Se recorre el arreglo de estaciones una única vez calculando el porcentaje y decidiendo si se muestra.

* **Cálculo de camino mínimo (BFS):**
  * *Complejidad:* `O(V + E)`, donde `V` es la cantidad de estaciones (vértices) y `E` la cantidad de ciclovías (aristas).
  * *Justificación:* El BFS explora el grafo por niveles, garantizando el camino más corto en grafos no ponderados.

**Resultados con datos de prueba:**
* Se cargaron 5 estaciones y 5 ciclovías.
* **Colisiones en la Tabla Hash:** 0.
* **Factor de carga final:** 0.0495 (5 elementos / 101 capacidad).
