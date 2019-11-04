// // gcc -Wall -pedantic -std=c99 main.c && ./a.out

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "String.h"
#include "intarray.h"


int main(int argc, char** argv){


	INTARRAY arr;
	intarray_init(&arr);

	for (int i = 0; i < 1000; i += 1){
		intarray_add(&arr, i);
	}

	for (int i = 0; i < 1000; i += 1){
		printf("%d ", arr.data[i]);
	}

	free(arr.data);


	return 0;
}
