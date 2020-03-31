#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

#include <stdio.h>
#include <math.h>

namespace multivector {
	typedef struct {
		double e0, x, y, z, yz, zy, xy, xyz;
	} MULTIVECTOR;

	void init(MULTIVECTOR *a);
	void product(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b);
	void rotate(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b);
	void print(MULTIVECTOR v);
	void printv(MULTIVECTOR v);
	char* str(char* buf, MULTIVECTOR v);

}

#endif


