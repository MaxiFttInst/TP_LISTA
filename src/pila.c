#include "pila.h"
#include "lista.h"

#include <stdlib.h>
#include <stdbool.h>

struct pila {
	Lista *lista;
};

Pila *pila_crear()
{
	Pila *nueva_pila = calloc(1, sizeof(Pila));
	if (nueva_pila == NULL)
		return NULL;
	nueva_pila->lista = lista_crear();
	return nueva_pila;
}
void pila_destruir(Pila *pila)
{
	if (pila == NULL)
		return;
	lista_destruir(pila->lista);
	free(pila);
}

void pila_destruir_todo(Pila *pila, void (*f)(void *))
{
	if (pila == NULL)
		return;
	lista_destruir_todo(pila->lista, f);
	free(pila);
}

//cada una de estas funciones es O(1)
size_t pila_cantidad(Pila *pila)
{
	if (pila == NULL)
		return 0;
	return lista_cantidad_elementos(pila->lista);
}
void *pila_tope(Pila *pila)
{
	if (pila == NULL)
		return 0;
	void *elemento_encontrado = NULL;
	lista_obtener_elemento(pila->lista, 0, &elemento_encontrado);
	return elemento_encontrado;
}
bool pila_apilar(Pila *pila, void *cosa)
{
	if (pila == NULL)
		return 0;
	lista_agregar_elemento(pila->lista, 0, cosa);
	return true;
}
void *pila_desapilar(Pila *pila)
{
	if (pila == NULL)
		return 0;
	void *elemento_quitado = NULL;
	lista_quitar_elemento(pila->lista, 0, &elemento_quitado);
	return elemento_quitado;
}
bool pila_esta_vacía(Pila *pila)
{
	if (pila == NULL)
		return 0;
	return lista_cantidad_elementos(pila->lista) == 0;
}
