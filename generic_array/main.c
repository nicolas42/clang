#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double* data;
	int length;
	int capacity;
	int index;
} ARRAY;

ARRAY* array_init(ARRAY* a){
	a->length = 0;
	a->capacity = 2;
	a->data = malloc(a->capacity * sizeof(double));
	return a;
}

ARRAY* array_add(ARRAY* a, double b){
	
	// reallocate if full
	if (a->length == a->capacity){
		a->capacity = 2 * a->capacity;
		a->data = realloc(a->data, a->capacity * sizeof(double));
		puts("Realloc! ");
	}
	a->data[a->length] = b;
	a->length++;
	return a;
}

ARRAY* array_clear(ARRAY* a){
	for (int i = 0; i < a->length; i++){
		a->data[i] = (uint64_t)0;
	}
	a->length = 0;
	return a;
}

int main(int argc, char** argv){

	ARRAY a;
	array_init(&a);

	for (int i = 0; i < 10; i++) { array_add(&a, (char)48+i); }
	puts("\r\n\r\nChars");
	for (int i = 0; i < 10; i++) { printf("%c", (char)a.data[i]); }
	array_clear(&a);

	for (int i = 0; i < 10; i++) { array_add(&a, (double)(1.0/i)); }
	puts("\r\n\r\nFloats");
	for (int i = 0; i < 10; i++) { printf("%f ", (double)a.data[i]); }
	array_clear(&a);

	for (int i = 0; i < 10; i++) { array_add(&a, (int)987*i); }
	puts("\r\n\r\nInts");
	for (int i = 0; i < 10; i++) { printf("%d ", (int)a.data[i]); }
	array_clear(&a);

	for (int i = 0; i < 10; i++) { array_add(&a, (int8_t)1000*i); }
	puts("\r\n\r\nLittle Ints :)");
	for (int i = 0; i < 10; i++) { printf("%d ", (int8_t)a.data[i]); }
	array_clear(&a);


	return 0;
}




// int main(int argc, char** argv){

// 	int capacity = 1024;
// 	int stride = 8;
// 	void* a = malloc(capacity * stride);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		((int*)a)[i*stride] = 1000*i;
// 	}

// 	for (int i = 0; i < 10; i++)
// 	{
// 		printf("%d ", ((int*)a)[i*stride]);
// 	}
	
// 	return 0;
// }
