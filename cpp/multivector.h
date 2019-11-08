#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

#include <stdio.h>
#include <math.h>
// #include "multivector.h"

namespace multivector {
	typedef struct {
		double e0, e1, e2, e3, e23, e31, e12, e123;
	} MULTIVECTOR;

	void init(MULTIVECTOR *a);
	void product(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b);
	void rotate(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b);
	void print(MULTIVECTOR v);
	void printv(MULTIVECTOR v);
	char* str(char* buf, MULTIVECTOR v);

}

#endif


