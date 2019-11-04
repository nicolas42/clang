// gcc -Wall -pedantic -std=c99 FloatArray.c && ./a.out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char INT_FORMAT[3] = "%f\0";
static const char INT_SEPARATOR[2] = " \0";

typedef struct {
	double* data;
	int length;
	int capacity;
	int index;
} FloatArray;

FloatArray* float_init(FloatArray* a){
	a->index = 0;
	a->length = 0;
	a->capacity = 2;
	a->data = malloc(a->capacity * sizeof(double));
	return a;
}

FloatArray* float_head(FloatArray* a){
	a->index = 0;
	return a;
}

FloatArray* float_tail(FloatArray* a){
	a->index = a->length;
	return a;
}

int float_is_head(FloatArray* a){
	return a->index == 0;
}

int float_is_tail(FloatArray* a){
	return a->index == a->length;
}

FloatArray* float_next(FloatArray* a){
	if (!float_is_tail(a)){
		a->index++;
	}
	return a;
}

FloatArray* float_back(FloatArray* a){
	if (!float_is_head(a)){
		a->index--;
	}
	return a;
}

FloatArray* float_append(FloatArray* a, double b){
	
	if (a->length == a->capacity){
		a->capacity = 2 * a->capacity;
		a->data = realloc(a->data, a->capacity * sizeof(double));
	}
	a->data[a->length] = b;
	a->length++;
	return a;
}

FloatArray* float_remove(FloatArray* a, int index){
	
	for (int i = index; i <= (a->length - 2); i += 1){
		a->data[i] = a->data[i + 1];
	}
	a->length--;
	return a;
}

FloatArray* float_insert(FloatArray* a, double b, int index){
	
	// append one b to ensure allocations are done
	float_append(a, b);
	
	for (int i = index; i <= a->length - 2; ++i){
		a->data[index + 1] = a->data[index];
	}
	// Actually set the b
	a->data[index] = b;
	a->length++;

	return a;
}

void float_print(FloatArray* a){
	printf("{");
	for (int i = a->index; i < a->length; i += 1){
		printf(INT_FORMAT, a->data[i]);
		printf(INT_SEPARATOR);
	}
	printf("}\n");
}

FloatArray* float_find(FloatArray* a, double b){

	for (int i = a->index; i < a->length; i += 1){
		if  (a->data[i] == b){
			a->index = i;
			return a;
		}
	}
	a->index = a->length;
	return a;
}

