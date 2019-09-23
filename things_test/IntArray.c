// gcc -Wall -pedantic -std=c99 IntArray.c && ./a.out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char INT_FORMAT[4] = "%d \0";
static const char INT_SEPARATOR[2] = " \0";

typedef struct {
	int* data;
	int length;
	int capacity;
	int index;
} IntArray;

IntArray* intarray_init(IntArray* a){
	a->index = 0;
	a->length = 0;
	a->capacity = 2;
	a->data = malloc(a->capacity * sizeof(int));
	return a;
}

IntArray* intarray_head(IntArray* a){
	a->index = 0;
	return a;
}

IntArray* intarray_tail(IntArray* a){
	a->index = a->length;
	return a;
}

int intarray_is_head(IntArray a){
	return a.index == 0;
}

int intarray_is_tail(IntArray a){
	return a.index == a.length;
}

IntArray* intarray_next(IntArray* a){
	if (!intarray_is_tail(*a)){
		a->index++;
	}
	return a;
}

IntArray* intarray_back(IntArray* a){
	if (!intarray_is_head(*a)){
		a->index--;
	}
	return a;
}

IntArray* intarray_append(IntArray* a, int b){
	
	if (a->length == a->capacity){
		a->capacity = 2 * a->capacity;
		a->data = realloc(a->data, a->capacity * sizeof(int));
	}
	a->data[a->length] = b;
	a->length++;
	return a;
}

IntArray* intarray_remove(IntArray* a, int index){
	
	for (int i = index; i <= (a->length - 2); i += 1){
		a->data[i] = a->data[i + 1];
	}
	a->length--;
	return a;
}

IntArray* intarray_insert(IntArray* a, int b, int index){
	
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

void intarray_print(IntArray* a){
	printf(" [ ");
	for (int i = a->index; i < a->length; i += 1){
		printf(INT_FORMAT, a->data[i]);
		printf(INT_SEPARATOR);
	}
	printf("]\n");
}

IntArray* intarray_find(IntArray* a, int b){

	for (int i = a->index; i < a->length; i += 1){
		if  (a->data[i] == b){
			a->index = i;
			return a;
		}
	}
	a->index = a->length;
	return a;
}

void test_dynamic_usage(){

	IntArray arr;
	intarray_init(&arr);

	int i;	
	for (i=0; i<10; i+=1){
		intarray_append(&arr, i);
	}

	intarray_print(&arr);

	intarray_print(intarray_find(&arr, 5));
	intarray_print(intarray_remove(&arr, 7));

	intarray_print(intarray_head(&arr));
	intarray_print(intarray_tail(&arr));

	free(arr.data);
}


int main(int argc, char** argv){

	printf("\nTest Dynamic Usage\n");
	test_dynamic_usage();

	printf("\n");
	return 0;
}




// void test_static_usage(void){
// 	int i = 0;
// 	int LENGTH = 5;
// 	int a[LENGTH];

// 	for (i = 0; i < LENGTH; ++i)
// 		thing_make(&a[i], rand(), rand());

// 	for (i = 0; i < LENGTH; ++i){
// 		thing_print(a[i]);
// 		printf(INT_ARRAY_SEPARATOR);
// 	}
// 	printf("\n");
// }

// int main(int argc, char** argv){

// 	printf("\nTest Dynamic Usage\n");
// 	test_dynamic_usage();

	// int N = 0;

	// // Argument Validation
	// switch (argc){
	// 	case 2:
	// 		N = atoi(argv[1]);
	// 		break;
	// 	case 1:
	// 		N = 5; // default
	// 		break;
	// 	default:
	// 	    usage();
	// 		break;
	// }

	// // char* buffer = malloc(sizeof(char));

	// printf("\nTest Dynamic Usage\n");
	// test_dynamic_usage();
	
	// printf("\nTest Static Usage\n");
	// test_static_usage();
	
	// // free(buffer);
	


	// printf("\nTest asprintf\n");
	// char* test = malloc(1);
	// asprintf(&test, "Hello you bastard\n"); // malloc

	// puts(test);
	// free(test);
	
	
// 	return 0;
// }
