#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

struct int_array {
	int *data;
	int length;
	int allocated;
};

void int_array_init(struct int_array *a);
void int_array_add(struct int_array *a, int b);
void int_array_printf(struct int_array a, char* format);
int int_array_main(int argc, int **argv);

#endif