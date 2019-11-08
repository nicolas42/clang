#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

#include <stdio.h>
#include <math.h>

typedef struct {
	double e0, x, y, z, yz, zy, xy, xyz;
} MULTIVECTOR;

void multivector_init(MULTIVECTOR *a);
void multivector_product(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b);
void multivector_rotate(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b);
void multivector_print(MULTIVECTOR v);
void multivector_printv(MULTIVECTOR v);
char* multivector_str(char* buf, MULTIVECTOR v);

/* https://stackoverflow.com/questions/4396140/why-doesnt-ansi-c-have-namespaces */


typedef struct {
	void (*init)(MULTIVECTOR *a);
	void (*product)(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b);
	void (*rotate)(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b);
	void (*print)(MULTIVECTOR v);
	void (*printv)(MULTIVECTOR v);
	char* (*str)(char* buf, MULTIVECTOR v);
}  LIB_MULTIVECTOR;

void lib_multivector_init(LIB_MULTIVECTOR *a);

extern const LIB_MULTIVECTOR lib_multivector;

#endif
