
#ifndef LISTA_INTERNAS_H
#define LISTA_INTERNAS_H

#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

bool interna_agregar_al_principio(Lista *lista, void *cosa);
bool interna_agregar_en_posicion(Lista *lista, size_t posicion, void *cosa);
bool interna_quitar_al_principio(Lista *lista, void **elemento_quitado);
bool interna_quitar_en_posicion(Lista *lista, size_t posicion,
				void **elemento_quitado);
#endif /* LISTA_INTERNAS_H */
