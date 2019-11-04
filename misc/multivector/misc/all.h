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

#ifndef MULTIVEC_H
#define MULTIVEC_H

#include <stdio.h>
#include "mystring.h"

void multivector_product(double *c, double *a, double *b);
void multivector_print(double *a);
void multivector_add(double *c, double *a, double *b);
void multivector_negate(double *c, double *a);
void multivector_init(double *a);
void multivector_copy(double *a, double *b);
// Rotate v by twice the angle between a and b
// And scale by |ab|^2 ???
void multivector_rotate(double *Rab, double *v, double *a, double *b);
String* multivector_string_add(String* a, double* mv);

#endif
