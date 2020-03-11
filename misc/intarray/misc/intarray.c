// gcc -Wall -pedantic -std=c99 INTARRAY.c && ./a.out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intarray.h"

static const char INT_FORMAT[3] = "%d\0";
static const char INT_SEPARATOR[2] = " \0";

INTARRAY* intarray_init(INTARRAY* a){
	a->index = 0;
	a->length = 0;
	a->capacity = 2;
	a->data = malloc(a->capacity * sizeof(int));
	return a;
}

INTARRAY* intarray_head(INTARRAY* a){
	a->index = 0;
	return a;
}

INTARRAY* intarray_tail(INTARRAY* a){
	a->index = a->length;
	return a;
}

int intarray_is_head(INTARRAY* a){
	return a->index == 0;
}

int intarray_is_tail(INTARRAY* a){
	return a->index == a->length;
}

INTARRAY* intarray_next(INTARRAY* a){
	if (!intarray_is_tail(a)){
		a->index++;
	}
	return a;
}

INTARRAY* intarray_back(INTARRAY* a){
	if (!intarray_is_head(a)){
		a->index--;
	}
	return a;
}

INTARRAY* intarray_append(INTARRAY* a, int b){
	
	if (a->length == a->capacity){
		a->capacity = 2 * a->capacity;
		a->data = realloc(a->data, a->capacity * sizeof(int));
	}
	a->data[a->length] = b;
	a->length++;
	return a;
}

INTARRAY* intarray_remove(INTARRAY* a, int index){
	
	for (int i = index; i <= (a->length - 2); i += 1){
		a->data[i] = a->data[i + 1];
	}
	a->length--;
	return a;
}

INTARRAY* intarray_insert(INTARRAY* a, int b, int index){
	
	// append one b to ensure allocations are done
	intarray_append(a, b);
	
	for (int i = index; i <= a->length - 2; ++i){
		a->data[index + 1] = a->data[index];
	}
	// Actually set the b
	a->data[index] = b;
	a->length++;

	return a;
}

void intarray_print(INTARRAY* a){
	printf("[");
	for (int i = a->index; i < a->length; i += 1){
		printf(INT_FORMAT, a->data[i]);
		printf(INT_SEPARATOR);
	}
	printf("]\n");
}

INTARRAY* intarray_find(INTARRAY* a, int b){

	for (int i = a->index; i < a->length; i += 1){
		if  (a->data[i] == b){
			a->index = i;
			return a;
		}
	}
	a->index = a->length;
	return a;
}

// void test_dynamic_usage(){

// 	INTARRAY str;
// 	intarray_init(&str);

// 	for (int i = 0; i < 10; i += 1){
// 		intarray_append(&str, i);
// 	}

// 	intarray_print(&str);

// 	intarray_print(intarray_find(&str, 3));
// 	intarray_print(intarray_remove(&str, 5));

// 	intarray_print(intarray_head(&str));
// 	intarray_print(intarray_tail(&str));

// 	while (!intarray_is_tail(&str)){

// 	}
// 	free(str.data);
// }


// int main(int argc, char** argv){

// 	printf("\nTest Dynamic Usage\n");
// 	test_dynamic_usage();

// 	printf("\n");
// 	return 0;
// }
