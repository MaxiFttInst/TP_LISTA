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

struct lista_iterador {
	Nodo *actual;
};

Lista *lista_crear()
{
	Lista *nueva_lista = calloc(1, sizeof(Lista));
	nueva_lista->cantidad = 0;
	nueva_lista->principio = NULL;
	nueva_lista->final = NULL;
	return nueva_lista;
}

void lista_destruir(Lista *lista)
{
	lista_destruir_todo(lista, NULL);
}

/**
 * Destruye la lista aplicando la funcion destructora (si no es NULL) a cada elemento.
 * */
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

/*
 * Devuelve la cantidad de elementos de la lista.
 * Una lista NULL tiene 0 elementos.
 */
size_t lista_cantidad_elementos(Lista *lista)
{
	if (lista == NULL)
		return 0;
	return lista->cantidad;
}

/**
 * Inserta un elemento en la lista en la posicion dada.
 *
 * Si la posición es mayor a la cantidad de elementos, es un error.
 *
 * Devuelve true si pudo, false en caso de error.
 *
 */
bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa)
{
	if (lista == NULL)
		return false;
	if (posicion > lista->cantidad)
		return false;

	Nodo *nodo_actual = lista->principio;
	Nodo *nodo_aux = NULL;
	bool resultado = false;
	if (posicion == 0 && lista->cantidad > 0) {
		Nodo *nuevo_nodo = calloc(1, sizeof(Nodo));
		nuevo_nodo->dato = cosa;
		nodo_aux = nodo_actual;
		nuevo_nodo->siguiente = nodo_aux;
		lista->principio = nuevo_nodo;
		lista->cantidad++;
		resultado = true;
	} else if (posicion == lista->cantidad) {
		resultado = lista_agregar_al_final(lista, cosa);
	} else {
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
		resultado = true;
	}
	return resultado;
}

/**
  * Inserta un elemento al final de la lista.
  */
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

/**
 * Elimina un elemento de la posicion dada.
 *
 * El elemento quitado se guarda en elemento_quitado (si se puede quitar y si no es null).
 *
 * En caso de error devuelve false, caso contrario true.
 */
bool lista_quitar_elemento(Lista *lista, size_t posicion,
			   void **elemento_quitado)
{
	if (lista == NULL)
		return false;
	if (lista->cantidad == 0)
		return false;
	if (posicion > lista->cantidad - 1)
		return false;

	Nodo *nodo_a_borrar = NULL;
	Nodo *nodo_actual = NULL;
	// Nodo *nodo_aux = NULL;
	bool resultado = false;
	if (posicion == 0) {
		*elemento_quitado = lista->principio->dato;
		nodo_a_borrar = lista->principio;
		lista->principio = lista->principio->siguiente;
		free(nodo_a_borrar);
		resultado = true;
	} else {
		nodo_actual = lista->principio;
		for (int i = 0; i < posicion - 1; i++) {
			nodo_actual = nodo_actual->siguiente;
		}
		nodo_a_borrar = nodo_actual->siguiente;
		*elemento_quitado = nodo_a_borrar->dato;
		nodo_actual->siguiente = nodo_a_borrar->siguiente;
		free(nodo_a_borrar);
		resultado = true;
	}
	lista->cantidad--;
	return resultado;
}

/**
 * Busca el elemento buscado en la lista y lo devuelve si lo encuentra.
 *
 * Para buscar el elemento, se aplica la función de comparacion.
 *
 * En caso de no encontrarlo devuelve NULL.
 */
void *lista_buscar_elemento(Lista *lista, void *buscado,
			    int (*comparador)(void *, void *))
{
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

/**
 * Obtiene el elemento almacenado en una posición
 *
 * Si la posicion es inválida es un error.
 *
 * El elemento encontrado se almacena en elemento_encontrado (a menos que sea NULL);
 *
 * Devuelve true si pudo obtener el elemento o false en caso de error.
 */
bool lista_obtener_elemento(Lista *lista, size_t posicion,
			    void **elemento_encontrado)
{
	Nodo *nodo_actual = lista->principio;
	for (int i = 0; i < posicion; i++) {
		nodo_actual = nodo_actual->siguiente;
	}
	*elemento_encontrado = nodo_actual->dato;
	return true;
}

/**
 * Recorre la lista aplicando la funcion f a cada elemento en orden.
 *
 * ctx se le pasa como segundo parámetro a f.
 *
 * Si la funcion devuelve true se debe seguir iterando, caso contrario no.
 *
 * Devuelve la cantidad de elementos iterados.
 * */
size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (lista == NULL)
		return 0;

	Nodo *nodo_actual = lista->principio;
	size_t elementos_iterados = 0;
	bool seguir_iterando = true;
	while (nodo_actual != NULL && seguir_iterando) {
		seguir_iterando = f(&nodo_actual->dato, ctx);
		nodo_actual = nodo_actual->siguiente;
		elementos_iterados++;
	}
	return elementos_iterados;
}

/**
 * Crea un iterador externo para una lista
 *
 * En caso de error devuelve NULL
 */
Lista_iterador *lista_iterador_crear(Lista *lista)
{
	Lista_iterador *iterador = calloc(1, sizeof(Lista));
	iterador->actual = lista->principio;
	return iterador;
}

/**
 * Devuelve true si hay siguiente.
 */
bool lista_iterador_hay_siguiente(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return false;
	return (iterador->actual->siguiente != NULL);
}

/**
 *
 * Hace que el iterador avance al siguiente elemento de la lista.
 *
 */
void lista_iterador_avanzar(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return;
	iterador->actual = iterador->actual->siguiente;
	return;
}

/**
 * Devuelve el elemento iterado
 */
void *lista_iterador_obtener_elemento_actual(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return NULL;
	return iterador->actual->dato;
}

/**
 * Eso
 */
void lista_iterador_destruir(Lista_iterador *iterador)
{
	if (iterador == NULL)
		return;
	free(iterador);
}
