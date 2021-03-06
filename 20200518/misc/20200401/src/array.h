#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double* data;
	size_t length;
	size_t capacity;
	size_t  index;
} ARRAY;

ARRAY* array_init(ARRAY* a);
ARRAY* array_add(ARRAY* a, double b);
ARRAY* array_clear(ARRAY* a);
ARRAY* array_print(ARRAY* a);
ARRAY* array_printf(ARRAY* a, char* format);

#endif
