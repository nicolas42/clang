// gcc -Wall -pedantic -std=c99 main.c && ./a.out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String.h"
#include "IntArray.h"
#include "FloatArray.h"

void test_string_dynamic_usage(){

	String str;
	string_init(&str);

	char* input = "Hello world";
	for (int i = 0; i < strlen(input); i += 1){
		string_append(&str, input[i]);
	}

	string_print(&str);

	string_print(string_find(&str, 'e'));
	string_print(string_remove(&str, 4));

	string_print(string_head(&str));
	string_print(string_tail(&str));

	// while (!string_is_tail(&str)){

	// }
	free(str.data);
}

void test_intarray_dynamic_usage(){

	IntArray str;
	intarray_init(&str);

	for (int i = 0; i < 10; i += 1){
		intarray_append(&str, i);
	}

	intarray_print(&str);

	intarray_print(intarray_find(&str, 3));
	intarray_print(intarray_remove(&str, 5));

	intarray_print(intarray_head(&str));
	intarray_print(intarray_tail(&str));

	free(str.data);
}

void test_floatarray_dynamic_usage(){

	FloatArray arr;
	float_init(&arr);

	double input[] = {1,2,3,4,5,6,234.234, 345.345,5};
	for (int i = 0; i < 9; i += 1){
		float_append(&arr, input[i]);
	}

	float_print(&arr);

	float_print(float_find(&arr, 234.234));
	float_print(float_remove(&arr, 4));

	float_print(float_head(&arr));
	float_print(float_tail(&arr));

	// while (!float_is_tail(&arr)){

	// }
	free(arr.data);
}


int main(int argc, char** argv){

	// printf("\nTest Dynamic Usage\n");
	test_string_dynamic_usage();
	test_intarray_dynamic_usage();
	test_floatarray_dynamic_usage();

	printf("\n");
	return 0;
}
