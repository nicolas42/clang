#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdlib.h>

typedef struct {
	char* data;
	int length;
	int allocated;
	int index;
} String;

String* string_init(String* a);
// void string_realloc_if_full(String** a);
String* string_add(String* a, char *b);
String* multivector_string_add(String* a, double* mv);

#endif
