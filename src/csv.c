#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGITUD_LINEA 1024

struct archivo_csv {
	FILE *file;
	char separador;
};

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo,
				      char separador)
{
	struct archivo_csv *archivo = calloc(1, sizeof(struct archivo_csv));

	archivo->file = fopen(nombre_archivo, "r");
	archivo->separador = separador;

	if (archivo->file == NULL) {
		free(archivo);
		archivo = NULL;
	}
	return archivo;
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	if (archivo == NULL) {
		return 0;
	}

	char line[LONGITUD_LINEA];
	if (fgets(line, sizeof(line), archivo->file) == NULL) {
		return 0;
	}

	size_t cols_exitosamente_leidas = 0;
	size_t col_index = 0;
	char *inicio = line;
	char *fin;

	while (col_index < columnas) {
		fin = inicio;
		while (*fin != '\0' && *fin != archivo->separador &&
		       *fin != '\n') {
			fin++;
		}

		if (*fin == archivo->separador) {
			*fin = '\0';
		} else if (*fin == '\n' || *fin == '\0') {
			if (inicio == fin)
				break;
		}

		if (funciones[col_index] != NULL) {
			if (funciones[col_index](inicio, ctx[col_index])) {
				cols_exitosamente_leidas++;
			}
		}

		inicio = fin + 1;
		col_index++;
	}

	return cols_exitosamente_leidas;
}
void cerrar_archivo_csv(struct archivo_csv *archivo)
{
	if (archivo == NULL)
		return;

	fclose(archivo->file);
	free(archivo);
}
