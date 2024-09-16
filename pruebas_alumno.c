#include "pa2m.h"
#include "src/lista.h"
#include <stdio.h>

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i == j, "i es igual a j (%d == %d)", i, j);
	pa2m_afirmar(2 * i == 10, "2*i es igual a 2 (%d)", 2 * i);
}
void prueba_creacion_destruccion_lista()
{
	printf(CYAN "CREAR/DESTRUIR LISTA");
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "La lista no es nula");
	lista_destruir(lista);
}
void prueba_insertar_elemento()
{
	printf(CYAN "INSERTAR ELEMENTO");
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "La lista no es nula");
	int algo = 5;
	lista_agregar_elemento(lista, 0, &algo);
	size_t cantidad_elem = lista_cantidad_elementos(lista);
	pa2m_afirmar(cantidad_elem == 1, "Hay un elemento (%d <-> 1)",
		     cantidad_elem);
	lista_destruir(lista);
}
int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS LISTA ===============");
	prueba_creacion_destruccion_lista();
	prueba_insertar_elemento();

	return pa2m_mostrar_reporte();
}
