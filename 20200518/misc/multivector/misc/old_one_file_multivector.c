// gcc -Wall -pedantic multivector.c && ./a.out

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


// Other Implementations
// https://rosettacode.org/wiki/Geometric_algebra

// Links
// https://marctenbosch.com/quaternions/
// https://www.euclideanspace.com/maths/algebra/clifford/d3/arithmetic/index.htm


// === Array Version ===
// Multivectors are implemented as 8 element arrays of doubles
// So if 'a' was a multivector then a[0] a[1:3] a[4:6] a[7] 
// would be the scalar, vector3, bivector3, and pseudo-scalar parts respectively.

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

void multivector_rotate(double *Rab, double *v, double *a, double *b){

	// Rotate v by twice the angle between a and b
	// And scale by |ab|^2 ???

	double ab[8], ba[8], v2[8];
	multivector_init(ab); multivector_init(ba); multivector_init(v2);

	multivector_product(ab, a, b);
	multivector_product(ba, b, a);

	multivector_product(v2, v, ab);
	multivector_product(Rab, ba, v2);
}

typedef struct {
	char* data;
	int length;
	int allocated;
	int index;
} String;

String* string_init(String* a){
	a->index = 0;
	a->length = 0;
	a->allocated = 2;
	a->data = malloc(a->allocated * sizeof(char));
	return a;
}

void string_realloc_if_full(String** a){
	if ((*a)->length == (*a)->allocated){
		(*a)->allocated *= 2;
		(*a)->data = realloc((*a)->data, (*a)->allocated * sizeof(char));
	}
}

String* string_add(String* a, char *b){

	int i;
	for (i = 0; b[i] != '\0'; i += 1){
		string_realloc_if_full(&a);
		a->data[a->length] = b[i];
		a->length++;
	}
	string_realloc_if_full(&a);	
	a->data[a->length] = '\0';

	return a;
}

String* string_add_multivector(String* a, double* mv){

	char b[8 * (2 + 0) + 11]; // 8 floating point values with 11 addition spaces
	snprintf(b, sizeof(b), "[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]", 
			mv[0], mv[1], mv[2], mv[3], mv[4], mv[5], mv[6], mv[7]);
	// %[flags][width][.precision][length]specifier
	string_add(a, b);
	return a;
}


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
	string_add_multivector(&s, v); string_add(&s, "\n");
	string_add_multivector(&s, a); string_add(&s, "\n");
	string_add_multivector(&s, b); string_add(&s, "\n");
	string_add_multivector(&s, Rab); string_add(&s, "\n");
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
