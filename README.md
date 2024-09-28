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
Lo que más vale la pena es desarrollar la explicación de la lista, porque la pila
y la cola son como un "alias" de los métodos de la lista, pero más
restringidos para que respeten la propia estructura.
Además, esas estructuras se explicarán más adelante.

Como nota a parte, hay que resaltar que en el código hay un apartado de
**funciones internas**: estas se encargan de ciertos casos comunes para
modularizar más el código y, de esa manera, este se explique más "por sí solo".

### lista_crear
La función `lista_crear` se encarga de crear una nueva lista. Esta operación
implica la asignación de memoria para la estructura de datos que representa la
lista. Dado que solo se realiza una operación de asignación y se inicializan
algunos punteros, la complejidad es constante, O(1).

### lista_destruir
Al invocar `lista_destruir`, se llama a la función `lista_destruir_todo`, que
recorre todos los nodos de la lista para liberar la memoria utilizada. Dado que
se debe visitar cada nodo para asegurarse de que no haya fugas de memoria, la
complejidad de esta operación es lineal, O(n), donde n es el número de
elementos en la lista.

### lista_destruir_todo
Similar a `lista_destruir`, esta función también recorre cada nodo de la lista
para liberarlo. Si se proporciona un destructor para liberar los datos, este
también se ejecutará en cada iteración. Por tanto, su complejidad es O(n).

### lista_cantidad_elementos
La función `lista_cantidad_elementos` simplemente accede al contador que
almacena la cantidad de elementos en la lista. Dado que no se realizan cálculos
ni recorridos, esta operación tiene una complejidad constante, O(1).

### lista_agregar_elemento
La complejidad de agregar un elemento a la lista varía según la posición:
- Si se agrega al principio o al final, es una operación constante, O(1), ya
   que solo se ajustan algunos punteros.
- Sin embargo, si se desea insertar en una posición intermedia, la función debe
   recorrer la lista hasta llegar a esa posición, lo que puede llevar hasta O(n)
   en el peor de los casos. Por lo tanto, la complejidad general de esta operación
   es O(n).

### lista_agregar_al_final
Agregar un elemento al final de la lista sólo requiere de anidar el nuevo nodo
con el último.
Esto da como resultado una complejidad constante, O(1).

### lista_quitar_elemento
La complejidad para quitar un elemento depende de la posición:
- Si se quita del principio, la operación es constante, O(1).
- Si se quita del medio o del final, es necesario recorrer la lista hasta esa
   posición, lo que puede llevar hasta O(n). Por lo tanto, la complejidad general
   es O(n).

### lista_buscar_elemento
Buscar un elemento en la lista implica recorrerla desde el principio hasta
encontrar el elemento buscado. En el peor de los casos, esto significa visitar
todos los nodos de la lista, lo que da como resultado una complejidad lineal,
O(n).

### lista_obtener_elemento
Obtener un elemento en una posición específica requiere recorrer la lista hasta
alcanzar dicha posición. En el peor de los casos, esto significa visitar n
nodos, por lo que la complejidad es O(n).

### lista_iterar_elementos
Esta función también recorre todos los elementos de la lista para aplicar una
función a cada uno de ellos. Al igual que en las búsquedas, la complejidad es
O(n), ya que podría ser necesario visitar todos los nodos.

### lista_iterador_crear
Crear un iterador para la lista implica simplemente reservar memoria y
establecer un puntero al primer nodo. Dado que no se requieren operaciones
complejas, la complejidad es O(1).

### lista_iterador_hay_siguiente
Comprobar si el iterador tiene un siguiente elemento solo requiere verificar el
puntero actual. Esta operación es constante, O(1).

### lista_iterador_avanzar
Avanzar el iterador al siguiente nodo es una operación sencilla que solo
modifica un puntero. Por lo tanto, la complejidad es O(1).

### lista_iterador_obtener_elemento_actual
Obtener el elemento actual del iterador implica acceder al puntero y devolver
el dato asociado. Dado que esta operación no involucra cálculos o recorridos,
tiene una complejidad constante, O(1).

### lista_iterador_destruir
Liberar la memoria del iterador es una operación directa que solo requiere
liberar el puntero. Por ende, la complejidad es O(1).

### Diagrama de la estructura en memoria
En este caso, suponemos que la lista está guardando datos de un arreglo
alojado en el stack.

<img width="130%" src="img/heap_stack_lista.svg">

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
siguiente) o dobles (donde cada nodo tiene referencias tanto al siguiente como al anterior)
. Esto permite una mayor flexibilidad en la manipulación de los nodos.
Entonces, por ejemplo, esto sería una lista válida:
<img width="90%" src="img/lista_valida.svg">

También esta es igualmente válida:
<img width="90%" src="img/lista_doble_valida.svg">

No obstante, esta implementación no sería válida:
<img width="90%" src="img/lista_no_valida.svg">

Esto se debe a que, en una lista, cada nodo se conecta secuencialmente.
El primer nodo no puede conectarse directamente al tercero y cuarto, ya que eso conformaría otra estructura.
#### Pila
Una pila es una estructura del tipo FILO (First In Last Out), es decir, el primero que entra es el último que sale.
Imaginemos que estamos apilando libros en una caja: si colocamos el libro de álgebra
primero y luego el de análisis matemático,
debemos quitar el de análisis para poder sacar el de álgebra.
Las operaciones básicas son:

- **push**: para agregar un elemento a la pila.
<img width="90%" src="img/pila_push.svg">

- **pop**: para eliminar el elemento más reciente.
<img width="90%" src="img/pila_pop.svg">

#### Cola
Una cola es como la que hacemos en el supermercado. Si llego primero, salgo primero,
y el último en llegar va al final, abreviándolo: FIFO (First In First Out). Entonces,
sólo puede salir el primero; una vez que salió, puede salir el segundo, y así
sucesivamente.
Las operaciones comunes en una cola son:

- **enqueue**: para agregar un elemento al final de la cola.
<img width="90%" src="img/cola_enqueue.svg">

- **dequeue**: para quitar el elemento que está en el frente.
<img width="90%" src="img/cola_dequeue.svg">

### Explica y analiza las diferencias de complejidad entre las implementaciones de lista simplemente enlazada, doblemente enlazada y vector dinámico para las operaciones:
#### Lista simplemente enlazada
   - **Insertar/obtener/eliminar al inicio O(1)**: La complejidad en este caso es O(1) porque sólo basta con insertar un nodo en el inicio y,
      el que antes era el nodo inicial pase a ser el siguiente del nuevo nodo.
   - **Insertar/obtener/eliminar al final O(1)**: Dado que debemos insertar un nodo al final  y tenemos una referencia del final
      en nuestra estructura, podemos ir al final e insertar nuestro nuevo nodo. Por este motivo, la complejidad es O(1) (aunque
      si no tuviéramos el puntero indicando el final, la complejidad sería O(n))
   - **Insertar/obtener/eliminar al medio O(n)**: Debemos recorrer la lista para insertar en la posición deseada, por ende, la complejidad
      es O(1).
#### Lista doblemente enlazada
   - **Insertar/obtener/eliminar al inicio O(1)**: En este punto, es igual a la LSE (lista simplemente enlazada).
   - **Insertar/obtener/eliminar al final O(1)**: También aquí, este punto es equivalente en la LSE.
   - **Insertar/obtener/eliminar al medio O(n)**: Al igual que en la LSE, la complejidad es la misma. **NO OBSTANTE**, esta estructura
      nos ofrece la posibilidad de ir hacia atrás, por ende, si queremos hacer una inserción/obtención/eliminación más rápida de algún
      elemento, podríamos establecer en nuestra estructura, por ejemplo, un puntero que indique al nodo que está en el medio del arreglo
      y, calculando las distancias para determinar si es conveniente, podríamos empezar a iterar en el medio, en vez en el principio. Entonces,
      por ejemplo, si nuestra lista tiene 10 elementos y el usuario pide el que está en la 4ta posición, podemos empezar por el medio (5ta 
      posición) y luego ir hacia atrás.
#### Vector dinámico
   - **Insertar/obtener/eliminar al inicio (O(n)/O(1)/O(n))**: En los casos de inserción y eliminación,
      debemos desplazar todos los elementos el arreglo, por este motivo, la complejidad es O(n). No obstante,
      en un vector dinámico podemos obtener el elemento con su índice, por ende su complejidad es O(1).
   - **Insertar/obtener/eliminar al final (O(1))**: No requerimos recorrer todo el vector ni desplazar sus elementos, sólo debemos
      redimencionar el vector y agregar en caso de inserción o indicar el índice del elemento para obtenerlo. En cuanto a la eliminación,
      tampoco debemos desplazar ningún elemento, porque no tiene siguiente. Por estos motivos, todas estas operaciones son O(1)
   - **Insertar/obtener/eliminar al medio (O(n)/O(1)/O(n))**: Tanto para la inserción como para la eliminación, requerimos desplazar los *n*
      elementos que hayan adelante, por eso la complejidad corresponde a O(n). Para obtener el elemento, la complejidad es O(1) por
      los mismos motivos explicados anteriormente.
# Explica la complejidad de las operaciones implementadas en tu trabajo para la pila y la cola.

## Preliminares
Tanto para la pila como para la cola, las funciones encargadas de inicializar y
destruir las estructuras son idénticas, es decir, las de inicialización son de
complejidad O(1) y las de destrucción O(n), dado que en el primer caso sólo debemos
asignar memoria, mientras que en el otro debemos recorrer toda la lista para
liberar los bloques de memoria.

## Complejidad en funciones de pila (Todas O(1))

### pila_cantidad
Debemos entrar a la estructura reutilizada de la lista y ver el dato correspondiente
a la cantidad, por eso, la complejidad es constante.

### pila_tope
Vemos qué hay en el tope de la pila, y como siempre es el primer elemento, la
complejidad es constante.

### pila_apilar
Siempre vamos a insertar un elemento al inicio y, siguiendo la analogía de los libros,
no debemos sacar otros antes para insertar uno en el tope, por ende, la complejidad
es constante.

### pila_desapilar
Muy similar a pila_apilar, siempre vamos a sacar el tope, por lo tanto, la complejidad
de la operación siempre será igual para cualquier cantidad de elementos.

### pila_esta_vacia
Al igual que pila cantidad, leemos el número almacenado en nuestra estructura
que nos indica la cantidad y, en vez de devolverlo, corroboramos que sea 0 para
devolver *true* o, caso contrario, *false*.

## Complejidad en funciones de cola (Todas O(1))

### cola_cantidad
Al igual que en la pila, en la cola mantenemos un contador que nos indica el número de elementos.
Acceder a esta variable es una operación constante, por lo que la complejidad es O(1).

### cola_frente
Para obtener el elemento que está en el frente de la cola, simplemente accedemos al primer elemento de la estructura.
No hay necesidad de recorrer la cola, así que la complejidad es constante.

### cola_encolar
Cuando encolamos un elemento, siempre lo añadimos al final de la cola.
Aplicando la implementación adecuada, no necesitamos mover otros elementos;
simplemente agregamos el nuevo elemento. Por lo tanto, la complejidad es O(1).

### cola_desencolar
Al desencolar, eliminamos el elemento que está al frente de la cola. Similar a *cola_frente*, esto se puede hacer accediendo
directamente al primer elemento y ajustando los punteros. Por lo tanto, la complejidad es O(1).

### cola_esta_vacia
Para verificar si la cola está vacía, simplemente revisamos el contador de elementos o el estado del puntero del frente.
Dado que esta operación no requiere recorrer la cola, la complejidad es O(1).
