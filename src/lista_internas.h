
#ifndef LISTA_INTERNAS_H
#define LISTA_INTERNAS_H

#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

// Agrega un elemento al principio de la lista
bool interna_agregar_al_principio(Lista *lista, void *cosa);

// Agrega la dirección de memoria de un elemento por "void *cosa" en la posición pedida
bool interna_agregar_en_posicion(Lista *lista, size_t posicion, void *cosa);

// Quita un elemento al principio y devuelve el elemento quitado por "void **elemento quitado"
bool interna_quitar_al_principio(Lista *lista, void **elemento_quitado);

// Quita un elemento en la posición pedida y devuelve el elemento quitado por "void **elemento quitado"
bool interna_quitar_en_posicion(Lista *lista, size_t posicion,
				void **elemento_quitado);

#endif /* LISTA_INTERNAS_H */
