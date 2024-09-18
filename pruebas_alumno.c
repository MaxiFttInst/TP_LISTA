#include "pa2m.h"
#include "src/lista.h"
#include <stdio.h>

int comparador_int(void *a, void *b)
{
	return *(int *)a - *(int *)b;
}
void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i == j, "i es igual a j (%d == %d)", i, j);
	pa2m_afirmar(2 * i == 10, "2*i es igual a 2 (%d)", 2 * i);
}
void prueba_creacion_destruccion_lista()
{
	printf(CYAN "CREAR/DESTRUIR LISTA \n");
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "La lista no es nula");
	lista_destruir(lista);
}
void prueba_destruir_lista_nula()
{
	printf(CYAN "DESTRUIR LISTA NULA\n");
	lista_destruir(NULL);
}
void prueba_insertar_elemento()
{
	printf(CYAN "INSERTAR ELEMENTO \n");
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "La lista no es nula");
	int algo = 5;
	lista_agregar_elemento(lista, 0, &algo);
	size_t cantidad_elem = lista_cantidad_elementos(lista);
	pa2m_afirmar(cantidad_elem == 1, "Hay un elemento (%d <-> 1)",
		     cantidad_elem);
	lista_destruir(lista);
}
void prueba_quitar_elementos()
{
	printf(CYAN "QUITAR ELEMENTOS \n");
	Lista *lista = lista_crear();
	int se_espera[5] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++) {
		lista_agregar_al_final(lista, &se_espera[i]);
	}
	void *elemento_quitado = NULL;
	lista_quitar_elemento(lista, 2, &elemento_quitado);
	pa2m_afirmar(*(int *)elemento_quitado == 3,
		     "Se quitó el elemento esperado");
	int esperado_sin_un_elemento[4] = { 1, 2, 4, 5 };
	void *elem_obtenido = NULL;
	bool obtenido = false;
	for (int i = 0; i < 4; i++) {
		obtenido = false;
		obtenido = lista_obtener_elemento(lista, (size_t)i,
						  &elem_obtenido);
		pa2m_afirmar(obtenido, "Se obtuvo un elemento");
		pa2m_afirmar(elem_obtenido != NULL, "Obtenido no es NULL");
		pa2m_afirmar(*(int *)elem_obtenido == esperado_sin_un_elemento[i],
			     "esperado %d <-> obtenido %d",
			     esperado_sin_un_elemento[i], *(int *)elem_obtenido);
	}
	bool quitado = lista_quitar_elemento(lista, 4, &elemento_quitado);
	pa2m_afirmar(!quitado, "La función no quitó el elemento que no existe");
	lista_quitar_elemento(lista, 3, &elemento_quitado);
	pa2m_afirmar(*(int *)elemento_quitado == 5,
		     "Se quitó el último elemento");
	lista_quitar_elemento(lista, 1, &elemento_quitado);
	pa2m_afirmar(*(int *)elemento_quitado == 2,
		     "Se quitó el elemento del medio");
	size_t cantidad_elem = lista_cantidad_elementos(lista);
	pa2m_afirmar(cantidad_elem == 2, "Hay 2 elementos <-> %d", cantidad_elem);
	lista_destruir(lista);

}
void prueba_integral_lista()
{
	printf(CYAN "PRUEBA INTEGEAL LISTA \n");
	int valores[20] = { 12, 34, 45, 65, 45, 76, 32, 76, 123, 45,
			    54, 6,  42, 6,  4,	34, 98, 47, 76,	 45 };
	int valores_final[3] = { 555, 777, 888 };
	int valores_esperados[23];
	int indice_valores = 0;
	for (int i = 19; i >= 0; i--) {
		valores_esperados[i] = valores[indice_valores];
		indice_valores++;
	}
	valores_esperados[20] = 555;
	valores_esperados[21] = 777;
	valores_esperados[22] = 888;
	printf(NORMAL "Orden de valores esperado: ");
	for (int i = 0; i < 23; i++) {
		printf("%d ", valores_esperados[i]);
	}
	printf("\n");

	bool agregado = false;
	Lista *lista = lista_crear();
	for (int i = 0; i < 20; i++) {
		agregado = false;
		agregado = lista_agregar_elemento(lista, 0, &valores[i]);
		pa2m_afirmar(agregado, "Se agregó el elemento al principio: %d",
			     valores[i]);
	}
	for (int i = 0; i < 3; i++) {
		agregado = false;
		agregado = lista_agregar_al_final(lista, &valores_final[i]);
		pa2m_afirmar(agregado, "Se agregó el elemnto al final: %d",
			     valores_final[i]);
	}
	pa2m_afirmar(lista_cantidad_elementos(lista) == 23, "Hay 23 elementos");
	bool quitado = false;
	void *elem_quitado = NULL;
	for (int i = 0; i < 23; i++) {
		quitado = lista_quitar_elemento(lista, 0, &elem_quitado);
		pa2m_afirmar(quitado, "Se quitó un elemento");
		pa2m_afirmar(elem_quitado != NULL, "Quitado no es NULL");
		pa2m_afirmar(*(int *)elem_quitado == valores_esperados[i],
			     "esperado %d <-> quitado %d", valores_esperados[i],
			     *(int *)elem_quitado);
	}
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0, "No hay elementos");
	for (int i = 0; i < 20; i++) {
		agregado = false;
		agregado = lista_agregar_elemento(lista, 0, &valores[i]);
		pa2m_afirmar(agregado, "Se agregó el elemento al principio: %d",
			     valores[i]);
	}
	for (int i = 0; i < 3; i++) {
		agregado = false;
		agregado = lista_agregar_al_final(lista, &valores_final[i]);
		pa2m_afirmar(agregado, "Se agregó el elemnto al final: %d",
			     valores_final[i]);
	}
	pa2m_afirmar(lista_cantidad_elementos(lista) == 23, "Hay 23 elementos");
	void *elem_obtenido = NULL;
	bool obtenido = false;
	for (int i = 0; i < 23; i++) {
		obtenido = false;
		obtenido = lista_obtener_elemento(lista, (size_t)i,
						  &elem_obtenido);
		pa2m_afirmar(obtenido, "Se obtuvo un elemento");
		pa2m_afirmar(elem_obtenido != NULL, "Obtenido no es NULL");
		pa2m_afirmar(*(int *)elem_obtenido == valores_esperados[i],
			     "esperado %d <-> obtenido %d",
			     valores_esperados[i], *(int *)elem_obtenido);
	}
	int *encontrado = NULL;
	for (int i = 0; i < 23; i++) {
		encontrado = lista_buscar_elemento(lista, &valores_esperados[i],
						   comparador_int);
		pa2m_afirmar(encontrado != NULL, "Encontrado no es NULL");
		pa2m_afirmar(*encontrado == valores_esperados[i],
			     " esperado %d <-> encontramos %d",
			     valores_esperados[i], *encontrado);
	}
	lista_destruir(lista);
}
int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS LISTA ===============");
	prueba_creacion_destruccion_lista();
	prueba_destruir_lista_nula();
	prueba_insertar_elemento();
	prueba_quitar_elementos();
	prueba_integral_lista();

	return pa2m_mostrar_reporte();
}
