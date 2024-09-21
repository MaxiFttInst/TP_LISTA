#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "src/lista.h"

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = _p1;
	struct pokemon *p2 = _p2;

	return strcmp(p1->nombre, p2->nombre);
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
		printf("Ingrese algún argumento válido");
		return -1;
	}
	printf("______ _____ _   __ ________  ________ _   _ \n"
	       "| ___ \\  _  | | / /|  ___|  \\/  |  _  | \\ | |\n"
	       "| |_/ / | | | |/ / | |__ | .  . | | | |  \\| |\n"
	       "|  __/| | | |    \\ |  __|| |\\/| | | | | . ` |\n"
	       "| |   \\ \\_/ / |\\  \\| |___| |  | \\ \\_/ / |\\  |\n"
	       "\\_|    \\___/\\_| \\_/\\____/\\_|  |_/\\___/\\_| \\_/ \n");
	return 0;
}
