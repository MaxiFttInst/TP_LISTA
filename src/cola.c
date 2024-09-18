#include "cola.h"
#include "lista.h"

struct cola {
	Lista *lista;
};

Cola *cola_crear()
{
	Cola *nueva_cola = calloc(1, sizeof(Cola));
	if (nueva_cola == NULL)
		return NULL;
	nueva_cola->lista = lista_crear();
	return nueva_cola;
}
void cola_destruir(Cola *cola)
{
	if (cola == NULL)
		return;
	lista_destruir(cola->lista);
	free(cola);
}
void cola_destruir_todo(Cola *cola, void (*f)(void *))
{
	if (cola == NULL)
		return;
	lista_destruir_todo(cola->lista, f);
	free(cola);
}

//cada una de estas funciones es O(1)
size_t cola_cantidad(Cola *cola)
{
	if (cola == NULL)
		return 0;
	return lista_cantidad_elementos(cola->lista);
}
void *cola_frente(Cola *cola)
{
	if (cola == NULL)
		return 0;
	void *elemento_encontrado = NULL;
	lista_obtener_elemento(cola->lista, 0, &elemento_encontrado);
	return elemento_encontrado;
}
bool cola_encolar(Cola *cola, void *cosa)
{
	if (cola == NULL)
		return 0;
	lista_agregar_al_final(cola->lista, cosa);
	return true;
}
void *cola_desencolar(Cola *cola)
{
	if (cola == NULL)
		return 0;
	void *elemento_quitado = NULL;
	lista_quitar_elemento(cola->lista, 0, &elemento_quitado);
	return elemento_quitado;
}
bool cola_esta_vacía(Cola *cola)
{
	if (cola == NULL)
		return 0;
	return lista_cantidad_elementos(cola->lista) == 0;
}
