#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char *data;
	int length;
	int allocated;
	int index;
	int stride;
} ARRAY;

void array_init(ARRAY* a, int stride);
ARRAY* array_add(ARRAY* a, char b);
ARRAY* array_clear(ARRAY* a);
// ARRAY* array_print(ARRAY* a);
// ARRAY* array_printf(ARRAY* a, char* format);




void array_init(ARRAY* a, int stride){
	a->length = 0;
	a->allocated = 2;
	a->data = (char*)malloc(a->allocated * sizeof(char));
	a->stride = stride;
}

ARRAY* array_add(ARRAY* a, char b){
	
	// reallocate if full
	if (a->length == a->allocated){
		a->allocated = 2 * a->allocated;
		a->data = (char*)realloc(a->data, a->allocated * sizeof(char));
		puts("Realloc! ");
	}
	a->data[a->length] = b;
	a->length++;
	return a;
}

ARRAY* array_clear(ARRAY* a){
	for (int i = 0; i < a->length; i++){
		a->data[i] = 0;
		/* Zero is represented with an exponent field of zero and a mantissa field of zero. Depending on the sign bit, it can be a positive zero or a negative zero. Thus, -0 and +0 are distinct values, though they are treated as equal. (https://blogs.msdn.microsoft.com/premk/2006/02/25/ieee-754-floating-point-special-values-and-ranges/)*/
	}
	a->length = 0;
	return a;
}

// ARRAY* array_print(ARRAY* a){
// 	for (int i = 0; i < a->length; i++){
// 		printf("%.3f ", a->data[i]);
// 	}
// 	return a;
// }

// ARRAY* array_printf(ARRAY* a, char* format){
// 	for (int i = 0; i < a->length; i++){
// 		printf(format, a->data[i]);
// 	}
// 	return a;
// }

int main(int argc, char** argv){

	ARRAY a;
	array_init(&a, 1);

	for (int i = 0; i < 10; i += a.stride) { 	array_add(&a, (char)48+i); 		}
	puts("\r\n\r\nChars");
	for (int i = 0; i < 10; i += a.stride) { 	printf("%c", (char)a.data[i]); 		}
	array_clear(&a);


	for (int i = 0; i < 10; i += a.stride) { 	array_add(&a, (double)(1.0/i)); 		}
	puts("\r\n\r\nFloats");
	for (int i = 0; i < 10; i += a.stride) { 	printf("%f ", (double)a.data[i]); 		}
	array_clear(&a);


	for (int i = 0; i < 10; i += a.stride) { 	array_add(&a, (int)987*i); 		}
	puts("\r\n\r\nInts");
	for (int i = 0; i < 10; i += a.stride) { 	printf("%d ", (int)a.data[i]); 		}
	array_clear(&a);


	for (int i = 0; i < 10; i += a.stride) { 	array_add(&a, (int8_t)1000*i); 		}
	puts("\r\n\r\nLittle Ints :)");
	for (int i = 0; i < 10; i += a.stride) { 	printf("%d ", (int8_t)a.data[i]); 		}
	array_clear(&a);



	return 0;
}
