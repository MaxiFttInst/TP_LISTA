#include "lista.h"
#include "lista_internas.h"

typedef struct nodo {
	void *dato;
	struct nodo *siguiente;

} Nodo;

struct lista {
	size_t cantidad;
	Nodo *principio;
	Nodo *final;
};

struct lista_iterador {
	Nodo *actual;
};

Lista *lista_crear()
{
	Lista *nueva_lista = calloc(1, sizeof(Lista));
	if (nueva_lista == NULL)
		return NULL;
	nueva_lista->cantidad = 0;
	nueva_lista->principio = NULL;
	nueva_lista->final = NULL;
	return nueva_lista;
}

void lista_destruir(Lista *lista)
{
	lista_destruir_todo(lista, NULL);
}

void lista_destruir_todo(Lista *lista, void (*destructor)(void *))
{
	if (lista == NULL)
		return;

	if (lista->cantidad == 0) {
		free(lista);
		return;
	}
	Nodo *nodo_actual = lista->principio;
	Nodo *nodo_a_borrar = NULL;
	while (nodo_actual != NULL) {
		nodo_a_borrar = nodo_actual;
		nodo_actual = nodo_a_borrar->siguiente;
		if (destructor != NULL)
			destructor(nodo_a_borrar->dato);
		free(nodo_a_borrar);
	}
	free(lista);
}

size_t lista_cantidad_elementos(Lista *lista)
{
	if (lista == NULL)
		return 0;
	return lista->cantidad;
}

bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa)
{
	if (lista == NULL)
		return false;
	if (posicion > lista->cantidad)
		return false;

	bool resultado = false;
	if (posicion == 0 && lista->cantidad > 0) {
		resultado = interna_agregar_al_principio(lista, cosa);
	} else if (posicion == lista->cantidad) {
		resultado = lista_agregar_al_final(lista, cosa);
	} else {
		resultado = interna_agregar_en_posicion(lista, posicion, cosa);
	}
	return resultado;
}

bool lista_agregar_al_final(Lista *lista, void *cosa)
{
	if (lista == NULL)
		return false;

	Nodo *nuevo_nodo = calloc(1, sizeof(Nodo));
	if (nuevo_nodo == NULL)
		return false;

	Nodo *nodo_anterior = NULL;

	nuevo_nodo->dato = cosa;
	if (lista->cantidad == 0) {
		lista->principio = nuevo_nodo;
		lista->final = nuevo_nodo;
	} else {
		nodo_anterior = lista->final;
		lista->final = nuevo_nodo;
		nodo_anterior->siguiente = nuevo_nodo;
	}
	lista->cantidad++;
	return true;
}

bool lista_quitar_elemento(Lista *lista, size_t posicion,
			   void **elemento_quitado)
{
	if (lista == NULL)
		return false;
	if (lista->cantidad == 0)
		return false;
	if (posicion > lista->cantidad - 1)
		return false;

	bool resultado = false;
	if (posicion == 0) {
		resultado =
			interna_quitar_al_principio(lista, elemento_quitado);
	} else {
		resultado = interna_quitar_en_posicion(lista, posicion,
						       elemento_quitado);
	}
	lista->cantidad--;
	return resultado;
}

void *lista_buscar_elemento(Lista *lista, void *buscado,
			    int (*comparador)(void *, void *))
{
	if (lista == NULL)
		return NULL;
	if (buscado == NULL || comparador == NULL)
		return NULL;
	Nodo *nodo_actual = lista->principio;
	void *resultado = NULL;
	bool encontrado = false;
	while (nodo_actual != NULL && !encontrado) {
		if (comparador(nodo_actual->dato, buscado) == 0) {
			resultado = nodo_actual->dato;
			encontrado = true;
		}
		nodo_actual = nodo_actual->siguiente;
	}
	return resultado;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion,
			    void **elemento_encontrado)
{
	if (lista == NULL)
		return false;
	if (posicion >= lista->cantidad)
		return false;
	if (elemento_encontrado == NULL)
		return true;
	Nodo *nodo_actual = lista->principio;
	for (int i = 0; i < posicion; i++) {
		nodo_actual = nodo_actual->siguiente;
	}
	*elemento_encontrado = nodo_actual->dato;
	return true;
}

size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (lista == NULL)
		return 0;

	Nodo *nodo_actual = lista->principio;
	size_t elementos_iterados = 0;
	bool seguir_iterando = true;
	while (nodo_actual != NULL && seguir_iterando) {
		seguir_iterando = f(nodo_actual->dato, ctx);
		nodo_actual = nodo_actual->siguiente;
		elementos_iterados++;
	}
	return elementos_iterados;
}

Lista_iterador *lista_iterador_crear(Lista *lista)
{
	if (lista == NULL)
		return NULL;
	Lista_iterador *iterador = calloc(1, sizeof(Lista));
	if (iterador == NULL)
		return NULL;
	iterador->actual = lista->principio;
	return iterador;
}

bool lista_iterador_hay_siguiente(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return false;
	return (iterador->actual != NULL);
}

void lista_iterador_avanzar(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return;
	if (iterador->actual == NULL)
		return;
	iterador->actual = iterador->actual->siguiente;
}

void *lista_iterador_obtener_elemento_actual(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return NULL;
	if (iterador->actual == NULL)
		return NULL;
	return iterador->actual->dato;
}

void lista_iterador_destruir(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return;
	free(iterador);
}
