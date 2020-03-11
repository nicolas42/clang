#include <stdlib.h>
#include "intarray.h"

INTARRAY* intarray_init(INTARRAY* a){
	// a->index = 0;
	a->length = 0;
	a->capacity = 1000;
	a->data = malloc(a->capacity * sizeof(int));
	return a;
}

INTARRAY* intarray_add(INTARRAY* a, int b){
	
	// reallocate if full
	if (a->length == a->capacity){
		a->capacity = 2 * a->capacity;
		a->data = realloc(a->data, a->capacity * sizeof(int));
	}
	a->data[a->length] = b;
	a->length++;
	return a;
}

