#include "int_array.h"
#include <stdio.h>
#include <stdlib.h>

void int_array_init(struct int_array *a){
	a->length = 0;
	a->allocated = 20;
	a->data = malloc(a->allocated * sizeof(int));
}

void int_array_add(struct int_array *a, int b){
	
	// reallocate if full
	if (a->length == a->allocated){
		a->allocated = 2 * a->allocated;
		a->data = realloc(a->data, a->allocated * sizeof(int));
		puts("Realloc! ");
	}
	a->data[a->length] = b;
	a->length++;
}

void int_array_printf(struct int_array a, char* format){
	int i;
	for (i = 0; i < a.length; i++){
		printf(format, a.data[i]);
	}
	return a;
}

int int_array_main(int argc, int **argv){

	struct int_array a;
	int_array_init(&a);

	int i;

	for ( i = 0; i < 10; i++) { 
		int_array_add(&a, i);
	}
	int_array_printf(a, "%d ");

	return 0;
}
