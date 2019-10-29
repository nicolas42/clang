#include <stdlib.h>
#include "mystring.h"

String* string_init(String* a){
	a->index = 0;
	a->length = 0;
	a->allocated = 2;
	a->data = malloc(a->allocated * sizeof(char));
	return a;
}

void string_realloc_if_full(String** a){
	if ((*a)->length == (*a)->allocated){
		(*a)->allocated *= 2;
		(*a)->data = realloc((*a)->data, (*a)->allocated * sizeof(char));
	}
}

String* string_add(String* a, char *b){

	int i;
	for (i = 0; b[i] != '\0'; i += 1){
		string_realloc_if_full(&a);
		a->data[a->length] = b[i];
		a->length++;
	}
	string_realloc_if_full(&a);	
	a->data[a->length] = '\0';

	return a;
}
