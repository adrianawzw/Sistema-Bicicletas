## Análisis Sección D (Redistribución)

* **Complejidad temporal en el peor caso:** O(2^n), donde *n* es la cantidad de estaciones.
* **Justificación:** El algoritmo de backtracking explora un árbol de decisiones binario (incluir o no incluir cada estación). En el peor de los casos (por ejemplo, si no se puede podar ninguna rama porque los faltantes son muy chicos), evalúa las 2^n combinaciones posibles.
* **Estructura utilizada:** Se utilizó un arreglo dinámico (`new[]`) para guardar el camino actual (los índices seleccionados) y evitar el uso de `std::vector`, cumpliendo con las restricciones del TP.