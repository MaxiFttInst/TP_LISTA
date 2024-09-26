#include "cola.h"
#include "lista.h"

typedef Lista cola;

Cola *cola_crear()
{
	return (Cola *)lista_crear();
}
void cola_destruir(Cola *cola)
{
	lista_destruir((Lista *)cola);
}
void cola_destruir_todo(Cola *cola, void (*f)(void *))
{
	lista_destruir_todo((Lista *)cola, f);
}

size_t cola_cantidad(Cola *cola)
{
	return lista_cantidad_elementos((Lista *)cola);
}
void *cola_frente(Cola *cola)
{
	void *elemento_encontrado = NULL;
	lista_obtener_elemento((Lista *)cola, 0, &elemento_encontrado);
	return elemento_encontrado;
}
bool cola_encolar(Cola *cola, void *cosa)
{
	return lista_agregar_al_final((Lista *)cola, cosa);
}
void *cola_desencolar(Cola *cola)
{
	void *elemento_quitado = NULL;
	lista_quitar_elemento((Lista *)cola, 0, &elemento_quitado);
	return elemento_quitado;
}
bool cola_esta_vacía(Cola *cola)
{
	return lista_cantidad_elementos((Lista *)cola) == 0;
}
