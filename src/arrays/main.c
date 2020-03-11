#include <stdlib.h>
#include <stdio.h>
#include "intarray.h"
#include "darray.h"
#include "pair_array.h"



int main(int argc, char** argv){

	int i;

	/* Integer Array */
	INTARRAY a; intarray_init(&a);
	printf("\nAdding a bunch of integers to the array\n");
	for (i = 48; i < 127; i++){
		intarray_add(&a, i);
	}
	printf("\nRetrieve a bunch of them\n");
	for (i = 0; i < a.length; i++){
		printf("%c ", a.data[i]);
	}
	printf("\nFree the array\n");
	free(a.data);

	/* Doubles Array */
	printf("\n\nDoubles\n\n");
	DARRAY d; darray_init(&d);
	for (i = 48; i < 127; i++){ darray_add(&d, i); }
	for (i = 0; i < d.length; i++){	printf("%f ", d.data[i]); }
	free(d.data);


	/* Pair Array */
	printf("\n\nPair Array\n\n");
	pair_array p;  pair_array_init(&p);
	for (i = 48; i < 127; i++){ 
		struct pair a; pair_make(&a, i,i); 
		pair_array_add(&p, a);
	}
	for (i = 0; i < p.length; i++){	
		printf("%dx%d ", p.data[i].x, p.data[i].y ); }
	free(p.data);


	return 0;
}





