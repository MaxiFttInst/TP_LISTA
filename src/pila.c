#include "pila.h"
#include "lista.h"

typedef Lista pila;

Pila *pila_crear()
{
	return (Pila *)lista_crear();
}
void pila_destruir(Pila *pila)
{
	lista_destruir((Lista *)pila);
}

void pila_destruir_todo(Pila *pila, void (*f)(void *))
{
	lista_destruir_todo((Lista *)pila, f);
}

size_t pila_cantidad(Pila *pila)
{
	return lista_cantidad_elementos((Lista *)pila);
}
void *pila_tope(Pila *pila)
{
	void *elemento_encontrado = NULL;
	lista_obtener_elemento((Lista *)pila, 0, &elemento_encontrado);
	return elemento_encontrado;
}
bool pila_apilar(Pila *pila, void *cosa)
{
	return lista_agregar_elemento((Lista *)pila, 0, cosa);
}
void *pila_desapilar(Pila *pila)
{
	void *elemento_quitado = NULL;
	lista_quitar_elemento((Lista *)pila, 0, &elemento_quitado);
	return elemento_quitado;
}
bool pila_esta_vacía(Pila *pila)
{
	return lista_cantidad_elementos((Lista *)pila) == 0;
}
