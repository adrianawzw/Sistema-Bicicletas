## B. Viajes y colas de espera

### B1. Viajes por estación y rango de fechas
**Complejidad:** O(n), donde n es la cantidad de viajes.

Se eligió una lista enlazada porque permite agregar nuevos viajes al final sin tener que cambiar el tamaño de la estructura. Para realizar la consulta, se debe recorrer la lista y verificar cuáles viajes cumplen con la estación de origen y el rango de fechas solicitado. Por eso, la complejidad es O(n). Además, las fechas en formato AAAAMMDD se pueden comparar directamente como números enteros.

### B2. Viajes de un usuario por DNI
**Complejidad:** O(n), donde n es la cantidad de viajes.

Se utiliza la misma lista enlazada del punto anterior, ya que no es necesario crear otra estructura para guardar los viajes. Se recorre la lista buscando los viajes que pertenecen al DNI indicado y, durante el recorrido, se suman los minutos de cada viaje. Como se revisan todos los registros una sola vez, la complejidad es O(n).

### B3. Bicicletas con más de X km
**Complejidad:** O(n), donde n es la cantidad de bicicletas.

Se utiliza el ABB porque las bicicletas ya se encuentran organizadas por su `bici_id`. Sin embargo, como el filtro se realiza según los kilómetros recorridos y no por el ID, es necesario revisar todos los nodos del árbol. Se utiliza el recorrido inorder para mostrar las bicicletas ordenadas por su ID.

### B4. Cola de espera por estación
**Complejidad:** `desencolar` es O(1); `encolar` es O(n), con n = usuarios en espera de esa estación.

Se eligió una cola enlazada (FIFO), una por cada estación, porque permite atender a los usuarios en el mismo orden en que llegaron: el primero que ingresa es el primero en recibir una bicicleta. Con punteros al frente y al final, retirar al primero no requiere mover los demás elementos, por eso `desencolar` es O(1). La operación `encolar` recorre la cola para validar que un mismo DNI no esté repetido, lo que mantiene el invariante de la clase a cambio de costar O(n). Cada estación tiene su propia cola para que la espera de una no afecte a las demás.

### B5. Cola de prioridad (Min-Heap) para el taller
**Complejidad:** O(log n) para insertar y extraer la bicicleta más urgente.

Se eligió un Min-Heap porque permite atender primero las bicicletas más urgentes: la de prioridad 1 queda en la raíz, antes que las de prioridad 3. Al insertar o extraer se realizan ajustes de subida o bajada que recorren solo la altura del árbol, por eso ambas operaciones son O(log n). Es una mejor opción que una lista ordenada, donde insertar un elemento puede costar O(n). Cuando dos bicicletas tienen la misma prioridad, sale primero la que ingresó antes al taller.