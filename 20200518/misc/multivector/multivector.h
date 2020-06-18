#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

typedef struct MULTIVECTOR {
	double e0, e1, e2, e3, e23, e31, e12, e123;
} MULTIVECTOR;

void multivector_init(MULTIVECTOR *a);
void multivector_product(MULTIVECTOR *c, MULTIVECTOR *a_arg, MULTIVECTOR *b_arg);
void multivector_rotate(MULTIVECTOR *Rab, MULTIVECTOR *v, MULTIVECTOR *a, MULTIVECTOR *b);

#endif
