#include <stdlib.h>
#include "darray.h"

DARRAY* darray_init(DARRAY* a){
	// a->index = 0;
	a->length = 0;
	a->capacity = 1000;
	a->data = malloc(a->capacity * sizeof(double));
	return a;
}

DARRAY* darray_add(DARRAY* a, double b){
	
	// reallocate if full
	if (a->length == a->capacity){
		a->capacity = 2 * a->capacity;
		a->data = realloc(a->data, a->capacity * sizeof(double));
	}
	a->data[a->length] = b;
	a->length++;
	return a;
}

