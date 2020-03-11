#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "intarray.h"
#include "darray.h"
// #include "pair_array.h"


#ifndef PAIR_ARRAY_H
#define PAIR_ARRAY_H

struct pair {
	int x; int y;
};

void pair_make(struct pair *a, int x, int y);

typedef struct {
	struct pair *data;
	int length;
	int allocated;
} pair_array;

void pair_array_init(pair_array* a);
void pair_array_add(pair_array* a, struct pair b);


void pair_make(struct pair *a, int x, int y){
	a->x = x; a->y = y;
}

void pair_array_init(pair_array* a){
	a->length = 0;
	a->allocated = 1000;
	a->data = malloc(a->allocated * sizeof(struct pair));
}

void pair_array_add(pair_array* a, struct pair b){
	
	// reallocate if full
	if (a->length == a->allocated){
		a->allocated = 2 * a->allocated;
		a->data = realloc(a->data, a->allocated * sizeof(struct pair));
	}
	a->data[a->length] = b;
	a->length++;
}

void pair_array_print(pair_array a){
	for (int i = 0; i < a.length; i++){	
		printf("%dx%d ", a.data[i].x, a.data[i].y ); 
	}
}

#endif


int main(int argc, char** argv){

	printf("\n\nPair Array Demo\n\n");
	
	pair_array px;  
	pair_array_init(&px);

	for (int i = 48; i < 127; i++){ 
		struct pair p; 
		pair_make(&p, i,i); 
		pair_array_add(&px, p);
	}
	pair_array_print(px);
	free(px.data);



/*

	INTARRAY a; intarray_init(&a);
	printf("\nAdding a bunch of integers to the array\n");
	for (int i = 48; i < 127; i++){
		intarray_add(&a, i);
	}
	printf("\nRetrieve a bunch of them\n");
	for (int i = 0; i < a.length; i++){
		printf("%d ", a.data[i]);
	}
	printf("\nFree the array\n");
	free(a.data);


	printf("\n\nDoubles\n\n");
	DARRAY d; darray_init(&d);
	for (int i = 48; i < 127; i++){ darray_add(&d, i); }
	for (int i = 0; i < d.length; i++){	printf("%f ", d.data[i]); }
	free(d.data);

*/




	return 0;
}





