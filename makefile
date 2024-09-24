VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CC = gcc

all: clean formatear valgrind-tp_lista valgrind-alumno

valgrind-alumno: clean pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.c pruebas_alumno.c
	$(CC) $(CFLAGS) src/*.c pruebas_alumno.c -o pruebas_alumno

valgrind-tp_lista: clean tp_lista
	valgrind $(VALGRIND_FLAGS) ./tp_lista "ejemplos/pokedex.csv"

tp_lista: src/*.c tp_lista.c
	$(CC) $(CFLAGS) src/*.c tp_lista.c -o tp_lista

formatear:
	clang-format --style=file -i *.c src/*.c src/*.h

clean:
	rm -f pruebas_alumno tp_lista
