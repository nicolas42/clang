#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

struct double_array {
	double *data;
	int length;
	int allocated;
};

void double_array_init(struct double_array *a);
void double_array_add(struct double_array *a, double b);
void double_array_printf(struct double_array a, char* format);
int double_array_main(int argc, int **argv);

#endif