## Sección C: Registro de bicicletas con Árbol Binario de Búsqueda (ABB)

### Pregunta de análisis: Altura del árbol y costo de búsqueda

**¿Qué altura tendría el árbol si las bicicletas se cargaran ordenadas por ID?**
Si las bicicletas se insertan en el árbol en orden estrictamente creciente (o decreciente) según su `bici_id`, el Árbol Binario de Búsqueda se degenera y se convierte en una estructura lineal (similar a una lista enlazada). Cada nuevo nodo se insertará siempre como el hijo derecho (o izquierdo) del nodo anterior.
En este caso, la altura del árbol sería igual a la cantidad de nodos (**\(n\)**).

**Ejemplo con 5 bicicletas:**
Si cargamos las bicicletas con IDs `501`, `502`, `503`, `504` y `505` en ese orden, el árbol queda así:

```text
501
  \
  502
    \
    503
      \
      504
        \
        505

La altura del árbol es de 5 niveles (o 4 aristas de profundidad).

¿Cómo afecta eso al costo de la búsqueda?
En un árbol binario de búsqueda balanceado, el costo de búsqueda (y de inserción/eliminación) es O(logn), porque en cada paso se descarta la mitad del árbol.
Sin embargo, en este caso degenerado (una lista), para buscar la bicicleta 505 el algoritmo debe recorrer todos y cada uno de los nodos anteriores. Por lo tanto, el costo de búsqueda en el peor caso pasa a ser O(n).

Opcional (Puntos extra): Eliminación en el ABB
Se implementó la eliminación de un nodo en el árbol contemplando correctamente los tres casos posibles:

* Nodo hoja (sin hijos): Se libera la memoria del nodo y se actualiza el puntero del padre a nullptr.

* Nodo con un solo hijo: Se "saltea" el nodo a eliminar, conectando el padre del nodo eliminado directamente con el hijo único (izquierdo o derecho).

* Nodo con dos hijos: Se busca el sucesor inorder (el nodo con el ID más pequeño dentro del subárbol derecho). Se copia el dato de ese sucesor al nodo que queremos eliminar, y luego se procede a eliminar el sucesor (que, por definición, tendrá a lo sumo un hijo derecho, cayendo en el caso 1 o 2).

