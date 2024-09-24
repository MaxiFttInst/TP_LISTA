#include "lista_internas.h"
#include "lista.h"

typedef struct nodo {
	void *dato;
	struct nodo *siguiente;

} Nodo;

struct lista {
	size_t cantidad;
	Nodo *principio;
	Nodo *final;
};

bool interna_agregar_al_principio(Lista *lista, void *cosa)
{
	Nodo *nodo_actual = lista->principio;
	Nodo *nodo_aux = NULL;
	Nodo *nuevo_nodo = calloc(1, sizeof(Nodo));
	if (nuevo_nodo == NULL)
		return false;
	nuevo_nodo->dato = cosa;
	nodo_aux = nodo_actual;
	nuevo_nodo->siguiente = nodo_aux;
	lista->principio = nuevo_nodo;
	lista->cantidad++;
	return true;
}

bool interna_agregar_en_posicion(Lista *lista, size_t posicion, void *cosa)
{
	Nodo *nodo_actual = lista->principio;
	Nodo *nodo_aux = NULL;
	nodo_actual = lista->principio;
	nodo_aux = NULL;
	Nodo *nuevo_nodo = calloc(1, sizeof(Nodo));
	if (nuevo_nodo == NULL)
		return false;
	for (int i = 0; i < posicion - 1; i++) {
		nodo_actual = nodo_actual->siguiente;
	}
	nodo_aux = nodo_actual->siguiente;
	nodo_actual->siguiente = nuevo_nodo;
	nuevo_nodo->siguiente = nodo_aux;
	nuevo_nodo->dato = cosa;
	lista->cantidad++;

	return true;
}

bool interna_quitar_al_principio(Lista *lista, void **elemento_quitado)
{
	Nodo *nodo_a_borrar = NULL;
	*elemento_quitado = lista->principio->dato;
	nodo_a_borrar = lista->principio;
	lista->principio = lista->principio->siguiente;
	free(nodo_a_borrar);
	return true;
}

bool interna_quitar_en_posicion(Lista *lista, size_t posicion,
				void **elemento_quitado)
{
	Nodo *nodo_a_borrar = NULL;
	Nodo *nodo_actual = NULL;

	nodo_actual = lista->principio;
	for (int i = 0; i < posicion - 1; i++) {
		nodo_actual = nodo_actual->siguiente;
	}
	nodo_a_borrar = nodo_actual->siguiente;
	*elemento_quitado = nodo_a_borrar->dato;
	nodo_actual->siguiente = nodo_a_borrar->siguiente;
	if (nodo_a_borrar == lista->final)
		lista->final = nodo_actual;
	free(nodo_a_borrar);
	return true;
}
