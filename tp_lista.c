#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "src/lista.h"
#include "src/csv.h"

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

void liberar_dato(void *_poke)
{
	free(((struct pokemon *)(_poke))->nombre);
	free(_poke);
}
int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = _p1;
	struct pokemon *p2 = _p2;

	return strcmp(p1->nombre, p2->nombre);
}

bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}

void cargar_pokemones_desde_csv(Lista *pokemones, char *nombre_csv)
{
	bool (*funciones[5])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter, leer_int,
						       leer_int, leer_int };
	struct pokemon lectura = { .nombre = NULL,
				   .tipo = 'Z',
				   .fuerza = 0,
				   .destreza = 0,
				   .resistencia = 0 };
	struct pokemon *a_lista = NULL;
	void *punteros[5] = { &lectura.nombre, &lectura.tipo, &lectura.fuerza,
			      &lectura.destreza, &lectura.resistencia };

	struct archivo_csv *csv = abrir_archivo_csv(nombre_csv, ';');

	while (leer_linea_csv(csv, 5, funciones, punteros) == 5) {
		a_lista = calloc(1, sizeof(struct pokemon));
		if (a_lista != NULL) {
			*a_lista = lectura;
			lista_agregar_al_final(pokemones, a_lista);
		}
	}
	cerrar_archivo_csv(csv);
}
void buscar_pokemon(Lista *pokemones, char *nombre)
{
	Lista_iterador *iterador = lista_iterador_crear(pokemones);
	struct pokemon *poke_actual = NULL;
	bool encontrado = false;
	while (lista_iterador_hay_siguiente(iterador) && !encontrado) {
		poke_actual = lista_iterador_obtener_elemento_actual(iterador);
		if (strcmp(poke_actual->nombre, nombre) == 0)
			encontrado = true;
		lista_iterador_avanzar(iterador);
	}
	if (encontrado) {
		printf("++=POKEMON ENCONTRADO=++ \n");
		printf("Nombre: %s \n", poke_actual->nombre);
		printf("Tipo: %c \n", poke_actual->tipo);
		printf("Fuerza: %d \n", poke_actual->fuerza);
		printf("Destreza: %d \n", poke_actual->destreza);
		printf("Resistencia: %d \n", poke_actual->resistencia);
	} else {
		printf("XX=POKEMON NO ENCONTRADO=XX \n");
	}
	lista_iterador_destruir(iterador);
}

bool mostrar_pokemon(void *_pokemon, void *_ctx)
{
	struct pokemon *poke = _pokemon;
	printf("\n\nNombre: %s \n", poke->nombre);
	printf("Tipo: %c \n", poke->tipo);
	printf("Fuerza: %d \n", poke->fuerza);
	printf("Destreza: %d \n", poke->destreza);
	printf("Resistencia: %d \n", poke->resistencia);
	return true;
}
void mostrar_pokemones(Lista *pokemones)
{
	lista_iterar_elementos(pokemones, mostrar_pokemon, NULL);
}
int main(int argc, char *argv[])
{
	//recibir un archivo por linea de comandos
	//abrir el archivo csv y parsear pokemones
	//agregar los pokemones a una lista
	//
	//El usuario puede elegir una de dos opciones
	//
	//1. Ingrear por teclado un nombre y el programa busca el pokemon en la lista
	//2. Listar todos los pokemones de la pokedex
	//
	//
	if (argc < 2) {
		printf("Ingrese algún argumento válido\n");
		return -1;
	}
	printf("______ _____ _   __ ________  ________ _   _ \n"
	       "| ___ \\  _  | | / /|  ___|  \\/  |  _  | \\ | |\n"
	       "| |_/ / | | | |/ / | |__ | .  . | | | |  \\| |\n"
	       "|  __/| | | |    \\ |  __|| |\\/| | | | | . ` |\n"
	       "| |   \\ \\_/ / |\\  \\| |___| |  | \\ \\_/ / |\\  |\n"
	       "\\_|    \\___/\\_| \\_/\\____/\\_|  |_/\\___/\\_| \\_/ \n");

	Lista *pokemones = lista_crear();
	int opcion = 1;
	char nombre[100] = "";
	cargar_pokemones_desde_csv(pokemones, argv[1]);
	printf("Puede elegir entre: \n");
	printf("(1) Buscar un pokemon\n");
	printf("(2) Mostrar todos los pokemon\n");
	printf("\n\nSu opción: ");
	scanf("%d", &opcion);
	switch (opcion) {
	case 1:
		printf("Escriba el nombre: ");
		scanf("%s", nombre);
		buscar_pokemon(pokemones, nombre);
		break;
	case 2:
		mostrar_pokemones(pokemones);
		break;
	default:
		printf("No especificó una opción válida");
	}
	lista_destruir_todo(pokemones, liberar_dato);
	return 0;
}
