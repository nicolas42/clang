// gcc -Wall -pedantic -std=c99 String.c && ./a.out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String.h"

static const char INT_FORMAT[3] = "%c\0";
static const char INT_SEPARATOR[1] = "\0";

String* string_init(String* a){
	a->index = 0;
	a->length = 0;
	a->capacity = 2;
	a->data = malloc(a->capacity * sizeof(char));
	return a;
}

String* string_head(String* a){
	a->index = 0;
	return a;
}

String* string_tail(String* a){
	a->index = a->length;
	return a;
}

int string_is_head(String* a){
	return a->index == 0;
}

int string_is_tail(String* a){
	return a->index == a->length;
}

String* string_next(String* a){
	if (!string_is_tail(a)){
		a->index++;
	}
	return a;
}

String* string_back(String* a){
	if (!string_is_head(a)){
		a->index--;
	}
	return a;
}

String* string_append(String* a, char b){
	
	if (a->length == a->capacity){
		a->capacity = 2 * a->capacity;
		a->data = realloc(a->data, a->capacity * sizeof(char));
	}
	a->data[a->length] = b;
	a->length++;
	return a;
}

String* string_remove(String* a, int index){
	
	for (int i = index; i <= (a->length - 2); i += 1){
		a->data[i] = a->data[i + 1];
	}
	a->length--;
	return a;
}

String* string_insert(String* a, char b, int index){
	
	// append one b to ensure allocations are done
	string_append(a, b);
	
	for (int i = index; i <= a->length - 2; ++i){
		a->data[index + 1] = a->data[index];
	}
	// Actually set the b
	a->data[index] = b;
	a->length++;

	return a;
}

void string_print(String* a){
	printf("{");
	for (int i = a->index; i < a->length; i += 1){
		printf(INT_FORMAT, a->data[i]);
		printf(INT_SEPARATOR);
	}
	printf("}\n");
}

String* string_find(String* a, char b){

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

// 	String str;
// 	string_init(&str);

// 	char* input = "Hello world";
// 	for (int i = 0; i < strlen(input); i += 1){
// 		string_append(&str, input[i]);
// 	}

// 	string_print(&str);

// 	string_print(string_find(&str, 'e'));
// 	string_print(string_remove(&str, 4));

// 	string_print(string_head(&str));
// 	string_print(string_tail(&str));

// 	while (!string_is_tail(&str)){

// 	}
// 	free(str.data);
// }


// int main(int argc, char** argv){

// 	printf("\nTest Dynamic Usage\n");
// 	test_dynamic_usage();

// 	printf("\n");
// 	return 0;
// }
