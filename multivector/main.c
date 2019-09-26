// gcc -Wall -pedantic multivector.c && ./a.out

// Other Implementations
// https://rosettacode.org/wiki/Geometric_algebra

// Links
// https://marctenbosch.com/quaternions/
// https://www.euclideanspace.com/maths/algebra/clifford/d3/arithmetic/index.htm


// === Array Version ===
// Multivectors are implemented as 8 element arrays of doubles
// So if 'a' was a multivector then a[0] a[1:3] a[4:6] a[7] 
// would be the scalar, vector3, bivector3, and pseudo-scalar parts respectively.

// typedef struct {
// 	double e0, e1, e2, e3, e23, e31, e12, e123;
// } Multivector;

// c->e0 	= a.e0*b.e0 + a.e1*b.e1 + a.e2*b.e2 + a.e3*b.e3 - a.e23*b.e23 - a.e31*b.e31 - a.e12*b.e12 - a.e123*b.e123;
// c->e1 	= a.e0*b.e1 + a.e1*b.e0 - a.e2*b.e12 + a.e12*b.e2 + a.e3*b.e31 - a.e31*b.e3 + a.e123*b.e23 + a.e23*b.e123;
// c->e2 	= a.e0*b.e2 + a.e2*b.e0 + a.e1*b.e12 - a.e12*b.e1 - a.e3*b.e23 + a.e23*b.e3 - a.e123*b.e31 - a.e31*b.e123;
// c->e3 	= a.e0*b.e3 + a.e3*b.e0 - a.e1*b.e31 + a.e31*b.e1 + a.e2*b.e23 - a.e23*b.e2 + a.e123*b.e12 + a.e12*b.e123;
// c->e23 	= a.e23*b.e0 + a.e0*b.e23 + a.e2*b.e3 - a.e3*b.e2 + a.e12*b.e31 - a.e31*b.e12 + a.e123*b.e1 + a.e1*b.e123;
// c->e31 	= a.e31*b.e0 + a.e0*b.e31 + a.e3*b.e1 - a.e1*b.e3 + a.e23*b.e12 - a.e12*b.e23 + a.e123*b.e2 + a.e2*b.e123;
// c->e12 	= a.e12*b.e0 + a.e0*b.e12 + a.e1*b.e2 - a.e2*b.e1 + a.e31*b.e23 - a.e23*b.e31 + a.e123*b.e3 + a.e3*b.e123;
// c->e123	= a.e0*b.e123 + a.e123*b.e0 + a.e1*b.e23 + a.e23*b.e1 + a.e2*b.e31 + a.e31*b.e2 + a.e3*b.e12 + a.e12*b.e3;



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "all.h"


void test_array_multivector(void){

	double v[8] = {0,1}; 
	double a[8] = {0,1}; 
	double b[8] = {0,1,0,1};
	double Rab[8] = {0};

	String s; 

	multivector_rotate(Rab, v, a, b);
	// multivector_product(ab, a, b);
	// multivector_product(ba, b, a);
	// multivector_product(v2, v, ab);
	// multivector_product(Rab, ba, v2);

	string_init(&s);
	string_add(&s, "// Perform rotation of v by twice the angle between a and b: v,a,b,Rab \n");
	multivector_string_add(&s, v); string_add(&s, "\n");
	multivector_string_add(&s, a); string_add(&s, "\n");
	multivector_string_add(&s, b); string_add(&s, "\n");
	multivector_string_add(&s, Rab); string_add(&s, "\n");

	printf("%s\n", s.data);

	// To reuse string
	// memset(s.data, '\0', s.allocated);
	// s.length = 0;

}


// === Struct Version ===

typedef struct {
	double e0, e1, e2, e3, e23, e31, e12, e123;
} Multivector;

void multivector_init2(Multivector *a){
	a->e0 = 0; a->e1 = 0; a->e2 = 0; a->e3 = 0; a->e23 = 0; a->e31 = 0; a->e12 = 0; a->e123 = 0; 
}

void multivector_product2(Multivector *c, Multivector *a_arg, Multivector *b_arg){
	Multivector a = *a_arg;
	Multivector b = *b_arg;
	// I've probably made a mistake somewhere o_o
	c->e0 	= a.e0*b.e0 	+ a.e1*b.e1 	+ a.e2*b.e2 	+ a.e3*b.e3 	- a.e23*b.e23 	- a.e31*b.e31 	- a.e12*b.e12 	- a.e123*b.e123;
	c->e1 	= a.e0*b.e1 	+ a.e1*b.e0 	- a.e2*b.e12 	+ a.e12*b.e2 	+ a.e3*b.e31 	- a.e31*b.e3 	+ a.e123*b.e23 	+ a.e23*b.e123;
	c->e2 	= a.e0*b.e2 	+ a.e2*b.e0 	+ a.e1*b.e12 	- a.e12*b.e1 	- a.e3*b.e23 	+ a.e23*b.e3 	- a.e123*b.e31 	- a.e31*b.e123;
	c->e3 	= a.e0*b.e3 	+ a.e3*b.e0 	- a.e1*b.e31 	+ a.e31*b.e1 	+ a.e2*b.e23 	- a.e23*b.e2 	+ a.e123*b.e12 	+ a.e12*b.e123;
	c->e23 	= a.e23*b.e0 	+ a.e0*b.e23 	+ a.e2*b.e3 	- a.e3*b.e2 	+ a.e12*b.e31 	- a.e31*b.e12 	+ a.e123*b.e1 	+ a.e1*b.e123;
	c->e31 	= a.e31*b.e0 	+ a.e0*b.e31 	+ a.e3*b.e1 	- a.e1*b.e3 	+ a.e23*b.e12 	- a.e12*b.e23 	+ a.e123*b.e2 	+ a.e2*b.e123;
	c->e12 	= a.e12*b.e0 	+ a.e0*b.e12 	+ a.e1*b.e2 	- a.e2*b.e1 	+ a.e31*b.e23 	- a.e23*b.e31 	+ a.e123*b.e3 	+ a.e3*b.e123;
	c->e123	= a.e0*b.e123 	+ a.e123*b.e0 	+ a.e1*b.e23 	+ a.e23*b.e1 	+ a.e2*b.e31 	+ a.e31*b.e2 	+ a.e3*b.e12 	+ a.e12*b.e3;

}

void multivector_rotate2(Multivector *Rab, Multivector *v, Multivector *a, Multivector *b){

	// Rotate v by twice the angle between a and b
	// And scale by |ab|^2 ???

	Multivector ab, ba, v2;
	multivector_init2(&ab); multivector_init2(&ba); multivector_init2(&v2);

	multivector_product2(&ab, a, b);
	multivector_product2(&ba, b, a);

	multivector_product2(&v2, v, &ab);
	multivector_product2(Rab, &ba, &v2);
}


void test_struct_multivector(void){
	
	// Multivector v,a,b,ab,ba,v2,Rab;
	// multivector_init2(&v); multivector_init2(&v); multivector_init2(&v); multivector_init2(&v); multivector_init2(&v); multivector_init2(&v); multivector_init2(&v); multivector_init2(&v); multivector_init2(&v); 

	Multivector v = {0,1};
	Multivector a = {0,1};
	Multivector b = {0,1,1};
	// Multivector ab = {0};
	// Multivector ba = {0};
	// Multivector v2 = {0};
	Multivector Rab = {0};

	char str[200];


	// Rotate x by 2 * angle between x and x+z
	multivector_rotate2(&Rab, &v, &a, &b);
	// multivector_product2(&ab, &a, &b);
	// multivector_product2(&ba, &b, &a);
	// multivector_product2(&v2, &v, &ab);
	// multivector_product2(&Rab, &ba, &v2);

	// Print Rab
	snprintf(str, sizeof(str), "[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]", 
			Rab.e0, Rab.e1, Rab.e2, Rab.e3, Rab.e23, Rab.e31, Rab.e12, Rab.e123);
	assert(0 == strcmp(str, "[0 0 2 0 0 0 0 0]"));
	printf("%s\n", str);

}



// === Dynamic Version with leaks :) ===

static double *garbage[1000];
static int garbage_length = 0;

double* mul(double *a, double *b){
	
	double *c = malloc(8 * sizeof(*c));
	garbage[garbage_length++] = c;

	c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3] - a[4]*b[4] - a[5]*b[5] - a[6]*b[6] - a[7]*b[7];

	c[1] = a[0]*b[1] + a[1]*b[0] - a[2]*b[6] + a[6]*b[2] + a[3]*b[5] - a[5]*b[3] + a[7]*b[4] + a[4]*b[7];
	c[2] = a[0]*b[2] + a[2]*b[0] + a[1]*b[6] - a[6]*b[1] - a[3]*b[4] + a[4]*b[3] - a[7]*b[5] - a[5]*b[7];
	c[3] = a[0]*b[3] + a[3]*b[0] - a[1]*b[5] + a[5]*b[1] + a[2]*b[4] - a[4]*b[2] + a[7]*b[6] + a[6]*b[7];

	c[4] = a[4]*b[0] + a[0]*b[4] + a[2]*b[3] - a[3]*b[2] + a[6]*b[5] - a[5]*b[6] + a[7]*b[1] + a[1]*b[7];
	c[5] = a[5]*b[0] + a[0]*b[5] + a[3]*b[1] - a[1]*b[3] + a[4]*b[6] - a[6]*b[4] + a[7]*b[2] + a[2]*b[7];
	c[6] = a[6]*b[0] + a[0]*b[6] + a[1]*b[2] - a[2]*b[1] + a[5]*b[4] - a[4]*b[5] + a[7]*b[3] + a[3]*b[7];

	c[7] = a[0]*b[7] + a[7]*b[0] + a[1]*b[4] + a[4]*b[1] + a[2]*b[5] + a[5]*b[2] + a[3]*b[6] + a[6]*b[3];
	
	return c;
}
void test_mul(void){

	double v[8] = {0,1}; 
	double a[8] = {0,1}; 
	double b[8] = {0,1,1};
	double *c;
	int i;


	c = mul(mul(b, mul(mul(a,v),a) ),b);
	printf("[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]\n", 
			c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);

	for (i = 0; i < garbage_length; i += 1){
		free(garbage[i]);
	}
}




int main(int argc, char **argv)
{

	test_array_multivector();

	printf("Other Versions\n");
	test_struct_multivector();
	test_mul();
	return 0;
}

// make_vector(&v, 1,0,0);
// make_bivector(&v, 1,0,0);
// make_complex(&v,1,1);
// make_quaternion(&v,1,2,3,4);
// make_scalar(&v,1);
// make_four_vector(&v,1,2,3,4);
