#include "pair_array.h"
#include <stdlib.h>

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

// pair_array* pair_array_printf(pair_array a, char *format){
// 	printf("%dx%d ", p.data[i].x, p.data[i].y ); 
// }

// 	for (i = 0; i < p.length; i++){	printf("%dx%d ", p.data[i].x, p.data[i].y ); }
