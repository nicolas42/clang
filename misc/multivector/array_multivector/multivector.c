#include "multivector.h"

void multivector_product(double *c, double *a, double *b){
	// I've probably made a mistake somewhere o_o
	c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3] - a[4]*b[4] - a[5]*b[5] - a[6]*b[6] - a[7]*b[7];

	c[1] = a[0]*b[1] + a[1]*b[0] - a[2]*b[6] + a[6]*b[2] + a[3]*b[5] - a[5]*b[3] + a[7]*b[4] + a[4]*b[7];
	c[2] = a[0]*b[2] + a[2]*b[0] + a[1]*b[6] - a[6]*b[1] - a[3]*b[4] + a[4]*b[3] - a[7]*b[5] - a[5]*b[7];
	c[3] = a[0]*b[3] + a[3]*b[0] - a[1]*b[5] + a[5]*b[1] + a[2]*b[4] - a[4]*b[2] + a[7]*b[6] + a[6]*b[7];

	c[4] = a[4]*b[0] + a[0]*b[4] + a[2]*b[3] - a[3]*b[2] + a[6]*b[5] - a[5]*b[6] + a[7]*b[1] + a[1]*b[7];
	c[5] = a[5]*b[0] + a[0]*b[5] + a[3]*b[1] - a[1]*b[3] + a[4]*b[6] - a[6]*b[4] + a[7]*b[2] + a[2]*b[7];
	c[6] = a[6]*b[0] + a[0]*b[6] + a[1]*b[2] - a[2]*b[1] + a[5]*b[4] - a[4]*b[5] + a[7]*b[3] + a[3]*b[7];

	c[7] = a[0]*b[7] + a[7]*b[0] + a[1]*b[4] + a[4]*b[1] + a[2]*b[5] + a[5]*b[2] + a[3]*b[6] + a[6]*b[3];

}

void multivector_print(double *a){
	printf("[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
}

void multivector_add(double *c, double *a, double *b){
	int i;
	for (i = 0; i < 8; i += 1){
		c[i] = a[i] + b[i];
	}
}

void multivector_negate(double *c, double *a){
	int i;
	for (i = 0; i < 8; i += 1){
		c[i] = - a[i];
	}
}

void multivector_init(double *a){
	int i;
	for (i = 0; i < 8; i += 1){
		a[i] = 0;
	}
}

void multivector_copy(double *a, double *b){
	int i;
	for (i = 0; i < 8; i += 1){
		a[i] = b[i];
	}
}

// Rotate v by twice the angle between a and b
// And scale by |ab|^2 ???
void multivector_rotate(double *Rab, double *v, double *a, double *b){

	double ab[8], ba[8], v2[8];
	multivector_init(ab); multivector_init(ba); multivector_init(v2);

	multivector_product(ab, a, b);
	multivector_product(ba, b, a);

	multivector_product(v2, v, ab);
	multivector_product(Rab, ba, v2);
}


String* multivector_string_add(String* a, double* mv){

	char b[8 * (2 + 0) + 11]; // 8 floating point values with 11 addition spaces
	snprintf(b, sizeof(b), "[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]", 
			mv[0], mv[1], mv[2], mv[3], mv[4], mv[5], mv[6], mv[7]);
	// %[flags][width][.precision][length]specifier
	string_add(a, b);
	return a;
}
