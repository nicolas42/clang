#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

#include <stdio.h>

typedef struct MULTIVECTOR {
	double e0, e1, e2, e3, e23, e31, e12, e123;
} MULTIVECTOR;

void multivector_init(MULTIVECTOR *a);
void multivector_product(MULTIVECTOR *c, MULTIVECTOR *a_arg, MULTIVECTOR *b_arg);
void multivector_rotate(MULTIVECTOR *Rab, MULTIVECTOR *v, MULTIVECTOR *a, MULTIVECTOR *b);


void multivector_print(MULTIVECTOR* v);
void vector_print(MULTIVECTOR* v);
void bivector_print(MULTIVECTOR* v);
void vector_set(MULTIVECTOR *a, double v1, double v2, double v3);
void vector_copy(MULTIVECTOR *a, MULTIVECTOR* b);

#endif
