#ifndef PILA_H_
#define PILA_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct pila Pila;

// Crea la pila
Pila *pila_crear();

// Destruye la pila
void pila_destruir(Pila *);

// Destruye la pila aplicando una función destructora
void pila_destruir_todo(Pila *, void (*f)(void *));

//cada una de estas funciones es O(1):

// Devuelve los cantidad de elementos almacenados.
size_t pila_cantidad(Pila *);

// Devuelve el elemento que está en el tope de la pila (el último insertado)
void *pila_tope(Pila *);

// Apila un elemento.
bool pila_apilar(Pila *, void *);

// Desapila un elemento.
void *pila_desapilar(Pila *);

// Devuelve true si la pila está vacía, caso contrario, devuelve false
bool pila_esta_vacía(Pila *);

#endif // PILA_H_
