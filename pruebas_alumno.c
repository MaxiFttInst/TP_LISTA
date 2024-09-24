#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"
#include <stdio.h>

int comparador_int(void *a, void *b)
{
	return *(int *)a - *(int *)b;
}
bool mostrar_ints(void *_dato, void *_ctx)
{
	int *dato = _dato;
	printf("%d->", *dato);
	return true;
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
void prueba_obtener_elemento()
{
	printf(CYAN "OBTENER ELEMENTO \n");
	Lista *lista = lista_crear();
	int valor = 5;
	lista_agregar_elemento(lista, 0, &valor);
	bool obtenido = lista_obtener_elemento(lista, 0, NULL);
	pa2m_afirmar(
		obtenido,
		"Obtener un elemento de la posicion 0 devuelve true aún cuando se pasa NULL como argumento");
	void *nro = NULL;
	lista_quitar_elemento(lista, 0, &nro);
	obtenido = lista_obtener_elemento(lista, 0, &nro);
	pa2m_afirmar(!obtenido,
		     "Obtener un elemento de la posicion 0 devuelve false");
	lista_destruir(lista);
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
	bool agregado = lista_agregar_elemento(lista, 5, &algo);

	pa2m_afirmar(!agregado,
		     "No se agregó el elemento en una posición inválida");
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
		pa2m_afirmar(
			*(int *)elem_obtenido == esperado_sin_un_elemento[i],
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
	pa2m_afirmar(cantidad_elem == 2, "Hay 2 elementos <-> %d",
		     cantidad_elem);
	lista_destruir(lista);
}

void prueba_quitar_elementos_y_agregar()
{
	printf(CYAN "QUITAR Y AGREGAR ELEMENTOS \n");
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
		pa2m_afirmar(
			*(int *)elem_obtenido == esperado_sin_un_elemento[i],
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
	pa2m_afirmar(cantidad_elem == 2, "Hay 2 elementos <-> %d",
		     cantidad_elem);
	printf("\n");
	lista_iterar_elementos(lista, mostrar_ints, NULL);
	printf("\n");
	int nro_final = 5;
	lista_agregar_al_final(lista, &nro_final);
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
void prueba_creacion_destruccion_iterador()
{
	Lista *lista = lista_crear();
	int elementos[5] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++)
		lista_agregar_al_final(lista, &elementos[i]);
	Lista_iterador *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL, "Iterador no es NULL");
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}
void prueba_iterador_lista_recorrer_elem()
{
	Lista *lista = lista_crear();
	int elementos[5] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++)
		lista_agregar_al_final(lista, &elementos[i]);
	Lista_iterador *i;
	for (i = lista_iterador_crear(lista); lista_iterador_hay_siguiente(i);
	     lista_iterador_avanzar(i)) {
		printf("%d ",
		       *(int *)lista_iterador_obtener_elemento_actual(i));
	}
	lista_iterador_destruir(i);
	lista_destruir(lista);
}

void prueba_crearcion_destruccion_cola()
{
	printf(CYAN "CREAR/DESTRUIR COLA \n");
	Cola *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Cola no es NULL");
	cola_destruir(cola);
}
void prueba_encolar_elem_cola()
{
	printf(CYAN "ENCOLAR \n");
	Cola *cola = cola_crear();
	int encolado_y_esperado[5] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++) {
		cola_encolar(cola, &encolado_y_esperado[i]);
	}
	pa2m_afirmar(5 == cola_cantidad(cola), "La cola tiene 5 elementos");
	pa2m_afirmar(1 == *(int *)cola_frente(cola),
		     "El primer elemento insertado es el primero");
	cola_destruir(cola);
}
void prueba_desencolar_elem_cola()
{
	printf(CYAN "DESENCOLAR \n");
	Cola *cola = cola_crear();
	int encolado_y_esperado[5] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++) {
		cola_encolar(cola, &encolado_y_esperado[i]);
	}
	int *quitado = NULL;
	quitado = cola_desencolar(cola);
	pa2m_afirmar(1 == *quitado, "Se quitó el elemento del principio");
	pa2m_afirmar(4 == cola_cantidad(cola), "La cola tiene 4 elementos");
	cola_destruir(cola);
}
void prueba_crearcion_destruccion_pila()
{
	printf(CYAN "CREAR/DESTRUIR PILA \n");
	Pila *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Cola no es NULL");
	pila_destruir(pila);
}
void prueba_apilar_elem_pila()
{
	printf(CYAN "APILAR \n");
	Pila *pila = pila_crear();
	int apilado[5] = { 1, 2, 3, 4, 5 };
	// int esperado[5] = {5,4,3,2,1};
	for (int i = 0; i < 5; i++) {
		pila_apilar(pila, &apilado[i]);
	}
	pa2m_afirmar(5 == pila_cantidad(pila), "La pila tiene 5 elementos");
	pa2m_afirmar(5 == *(int *)pila_tope(pila),
		     "El tope es el último insertado");
	pila_destruir(pila);
}
void prueba_desapilar_elem_pila()
{
	printf(CYAN "DESAPILAR \n");
	Pila *pila = pila_crear();
	int apilado[5] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++) {
		pila_apilar(pila, &apilado[i]);
	}
	int *desapilado = NULL;
	for (int i = 4; i >= 0; i--) {
		desapilado = pila_desapilar(pila);
		pa2m_afirmar(*desapilado == apilado[i],
			     "desapilado %d <-> esperado %d", *desapilado,
			     apilado[i]);
		pa2m_afirmar(i == pila_cantidad(pila),
			     "La pila tiene %d elementos", i);
	}
	pa2m_afirmar(pila_esta_vacía(pila), "La pila está vacía");
	pila_destruir(pila);
}
int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS LISTA ===============");
	prueba_creacion_destruccion_lista();
	prueba_destruir_lista_nula();
	prueba_obtener_elemento();
	prueba_insertar_elemento();
	prueba_quitar_elementos();
	prueba_quitar_elementos_y_agregar();
	prueba_integral_lista();
	pa2m_nuevo_grupo(
		"============== PRUEBAS ITERADOR LISTA ===============");
	prueba_creacion_destruccion_iterador();
	prueba_iterador_lista_recorrer_elem();
	pa2m_nuevo_grupo("============== PRUEBAS COLA ===============");
	prueba_crearcion_destruccion_cola();
	prueba_encolar_elem_cola();
	prueba_desencolar_elem_cola();
	pa2m_nuevo_grupo("============== PRUEBAS PILA ===============");
	prueba_crearcion_destruccion_pila();
	prueba_apilar_elem_pila();
	prueba_desapilar_elem_pila();

	return pa2m_mostrar_reporte();
}
