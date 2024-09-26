#ifndef COLA_H_
#define COLA_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct cola Cola;

// Devuelve un puntero tipo cola
Cola *cola_crear();
// Destruye la cola
void cola_destruir(Cola *);

// Destruye la cola aplicando una función destructora
void cola_destruir_todo(Cola *, void (*f)(void *));

//cada una de estas funciones es O(1):

// Devuelve la cantidad de elementos almacenados
size_t cola_cantidad(Cola *);

// Devuelve el elemento que está al frente
void *cola_frente(Cola *);

// Inserta un elemento al final de la cola
bool cola_encolar(Cola *, void *);

// Quita el elemnto del principio
void *cola_desencolar(Cola *);

// Devuelve true si la cola está vacía, caso contrario, devuelve false
bool cola_esta_vacía(Cola *);

#endif // COLA_H_
