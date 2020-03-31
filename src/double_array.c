#include "double_array.h"
#include <stdio.h>
#include <stdlib.h>

void double_array_init(struct double_array *a){
	a->length = 0;
	a->allocated = 20;
	a->data = malloc(a->allocated * sizeof(double));
}

void double_array_add(struct double_array *a, double b){
	
	// reallocate if full
	if (a->length == a->allocated){
		a->allocated = 2 * a->allocated;
		a->data = realloc(a->data, a->allocated * sizeof(double));
		puts("Realloc! ");
	}
	a->data[a->length] = b;
	a->length++;
}

void double_array_printf(struct double_array a, char* format){
	int i;
	for (i = 0; i < a.length; i++){
		printf(format, a.data[i]);
	}
}

int double_array_main(int argc, int **argv){

	struct double_array a;
	double_array_init(&a);

	int i;

	for ( i = 0; i < 10; i++) { 
		double_array_add(&a, (double)i);
	}
	double_array_printf(a, "%f ");

	return 0;
}

