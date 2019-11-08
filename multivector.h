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


#endif
