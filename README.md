<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA LISTA

## Alumno: Maximiliano Fittipaldi - 111676 - mafittipaldi@fi.uba.ar

- Para compilar y correr todo con valgrind:

```bash
make
```

- Para correr pruebas con valgrind:

```bash
make valgrind-alumno
```

- Para correr el tp_lista (enunciado):
```bash
make valgrind-tp_lista
```

---

##  Funcionamiento

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluír **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
### ¿Qué es una lista/pila/cola?
#### Lista:
Una lista consiste en un conjunto de nodos que se van conectando secuencialmente
entre ellos. Cada nodo es de la forma:
    - dato
    - siguiente
    - anterior
Las listas pueden ser simplemente enlazadas (donde cada nodo solo tiene una referencia al
siguiente) o dobles (donde cada nodo tiene referencias tanto al siguiente como al anterio
r). Esto permite una mayor flexibilidad en la manipulación de los nodos.
Entonces, por ejemplo, esto sería una lista válida:
<img width="70%" src="img/lista_valida.svg">

También esta es igualmente válida:
<img width="70%" src="img/lista_doble_valida.svg">

No obstante, esta implementación no sería válida:
<img width="70%" src="img/lista_no_valida.svg">

Esto se debe a que, en una lista, cada nodo se conecta secuencialmente.
El primer nodo no puede conectarse directamente al tercero y cuarto, ya que eso conformaría otra estructura.
#### Pila
Una pila es una estructura del tipo FILO (First In Last Out), es decir, el primero que entra es el último que sale.
Imaginemos que estamos apilando libros en una caja: si colocamos el libro de álgebra
primero y luego el de análisis matemático,
debemos quitar el de análisis para poder sacar el de álgebra.
Las operaciones básicas son:

- **push**: para agregar un elemento a la pila.
- **pop**: para eliminar el elemento más reciente.
#### Cola
Una cola es como la que hacemos en el supermercado. Si llego primero, salgo primero,
y el último en llegar va al final, abreviándolo: FIFO (First In First Out). Entonces,
sólo puede salir el primero; una vez que salió, puede salir el segundo, y así
sucesivamente.
Las operaciones comunes en una cola son:

- **enqueue**: para agregar un elemento al final de la cola.
- **dequeue**: para quitar el elemento que está en el frente.
### Explica y analiza las diferencias de complejidad entre las implementaciones de lista simplemente enlazada, doblemente enlazada y vector dinámico para las operaciones:
#### Lista simplemente enlazada
   - Insertar/obtener/eliminar al inicio O(1)
   - Insertar/obtener/eliminar al final O(1)
   - Insertar/obtener/eliminar al medio O(n)
#### Lista doblemente enlazada
   - Insertar/obtener/eliminar al inicio O(1)
   - Insertar/obtener/eliminar al final O(1)
   - Insertar/obtener/eliminar al medio O(n)
#### Vector dinámico
   - Insertar/obtener/eliminar al inicio O(n)
   - Insertar/obtener/eliminar al final O(1)
   - Insertar/obtener/eliminar al medio O(n)
# Explica la complejidad de las operaciones implementadas en tu trabajo para la pila y la cola.
