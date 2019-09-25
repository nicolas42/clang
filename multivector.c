// gcc -Wall -pedantic multivector.c && ./a.out

// https://marctenbosch.com/quaternions/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void multivector_product(double *c, double *a, double *b){
	// I've probably made a mistake somewhere o_o
	c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3] - a[4]*b[4] - a[5]*b[5] - a[6]*b[6] - a[7]*b[7];

	c[1] = a[0]*b[1] + a[1]*b[0] - a[2]*b[6] + a[6]*b[2] + a[3]*b[5] - a[5]*b[3] + a[7]*b[4] + a[4]*b[7];
	c[2] = a[0]*b[2] + a[2]*b[0] + a[1]*b[6] - a[6]*b[1] - a[3]*b[4] + a[4]*b[3] - a[7]*b[5] - a[5]*b[7];
	c[3] = a[0]*b[3] + a[3]*b[0] - a[1]*b[5] + a[5]*b[1] + a[2]*b[4] - a[4]*b[3] + a[7]*b[6] + a[6]*b[7];

	c[4] = a[4]*b[0] + a[0]*b[4] + a[2]*b[3] - a[3]*b[2] + a[6]*b[5] - a[5]*b[6] + a[7]*b[1] + a[1]*b[7];
	c[5] = a[5]*b[0] + a[0]*b[5] + a[3]*b[1] - a[1]*b[3] + a[4]*b[6] - a[6]*b[4] + a[7]*b[2] + a[2]*b[7];
	c[6] = a[6]*b[0] + a[0]*b[6] + a[1]*b[2] - a[2]*b[1] + a[5]*b[4] - a[4]*b[5] + a[7]*b[3] + a[3]*b[7];

	c[7] = a[0]*b[7] + a[7]*b[0] + a[1]*b[4] + a[4]*b[1] + a[2]*b[5] + a[5]*b[2] + a[3]*b[6] + a[6]*b[3];
}


void multivector_print(double *a){
	printf("[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
}

void multivector_add(double *c, double *a, double *b){
	for (int i = 0; i < 8; i += 1){
		c[i] = a[i] + b[i];
	}
}

void multivector_negate(double *c, double *a){
	for (int i = 0; i < 8; i += 1){
		c[i] = - a[i];
	}
}

void multivector_init(double *a){
	for (int i = 0; i < 8; i += 1){
		a[i] = 0;
	}
}

void multivector_copy(double *a, double *b){
	for (int i = 0; i < 8; i += 1){
		a[i] = b[i];
	}
}

void multivector_rotate(double *Rab, double *v, double *a, double *b){

	// Rotate v by twice the angle between a and b
	// And scale it by |ab|^2 I think

	double ab[8], ba[8], v2[8];
	multivector_init(ab); multivector_init(ba); multivector_init(v2);

	multivector_product(ab, a, b);
	multivector_product(ba, b, a);

	multivector_product(v2, v, ab);
	multivector_product(Rab, ba, v2);
}


// make_vector(&v, 1,0,0);
// make_bivector(&v, 1,0,0);
// make_complex(&v,1,1);
// make_quaternion(&v,1,2,3,4);
// make_scalar(&v,1);
// make_four_vector(&v,1,2,3,4);

// typedef struct {
// 	double x,y,z;
// }Vector;
// typedef struct {
// 	double yz,zx,xy;
// }Bivector;

// typdef struct {
// 	double scalar;
// 	Vector vector;
// 	Bivector multivector;
// 	double pseudoscalar;
// } Multivector;

// typdef struct {
// 	double e0, e1, e2, e3, e23, e31, e12;
// } Multivector;

typedef struct {
	char* data;
	int length;
	int capacity;
	int index;
} String;

String* string_init(String* a){
	a->index = 0;
	a->length = 0;
	a->capacity = 2;
	a->data = malloc(a->capacity * sizeof(char));
	return a;
}

String* string_add(String* a, char *b){

	for (int i = 0; b[i] != '\0'; i += 1){
		if (a->length == a->capacity){
			a->capacity *= 2;
			a->data = realloc(a->data, a->capacity * sizeof(char));
		}
		a->data[a->length] = b[i];
		a->length++;

	}	
	a->data[a->length] = '\0';

	return a;
}

String* string_add_multivector(String* a, double* mv){

	char buf[8 * (2 + 0) + 11]; // 8 floating point values with 11 addition spaces
	snprintf(buf, sizeof(buf), "[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]", 
			mv[0], mv[1], mv[2], mv[3], mv[4], mv[5], mv[6], mv[7]);
	// %[flags][width][.precision][length]specifier

	for (int i = 0; buf[i] != '\0'; i += 1){
		if (a->length == a->capacity){
			a->capacity *= 2;
			a->data = realloc(a->data, a->capacity * sizeof(char));
		}
		a->data[a->length] = buf[i];
		a->length++;

	}	
	a->data[a->length] = '\0';

	return a;
}

// Test Multiplying two 3 dimensional multivectors
// https://www.euclideanspace.com/maths/algebra/clifford/d3/arithmetic/index.htm
int main(int argc, char **argv)
{

	// v.x=2;
	// v.y=3;
	// v.xy=2;
	// v.yz=3;

	// v 0 1 
	// a 0 1
	// b 0 1 1

	double v[8] = {0,1}; 
	double a[8] = {0,1}; 
	double b[8] = {0,1,1};

	double ab[8], ba[8], v2[8], Rab[8];
	multivector_init(ab); multivector_init(ba); multivector_init(v2); multivector_init(Rab); 

	multivector_rotate(Rab, v, a, b);
	// multivector_product(ab, a, b);
	// multivector_product(ba, b, a);
	// multivector_product(v2, v, ab);
	// multivector_product(Rab, ba, v2);


	printf("// Perform rotation of v by twice the angle between a and b: v,a,b,Rab \n");
	multivector_print(v); printf("\n");
	multivector_print(a); printf("\n");
	multivector_print(b); printf("\n");
	multivector_print(Rab); printf("\n");


	String str; string_init(&str);

	// string_add(&str, "Hello ");
	// string_add(&str, "World!");
	// printf("%s\n", str.data);
	
	memset(str.data, '\0', str.capacity);
	str.length = 0;
	string_add_multivector(&str, (double[8]){0,0,1,});
	string_add_multivector(&str, b);
	printf("%s\n", str.data);




	return 0;
}




// int main(int argc, char **argv)
// {
// 	// Multiply two multivectors a and b to make c
// 	// Note: Bivectors have dimensions e_23 e_31 e_12
// 	// Vectors have dimensions e_1 e_2 e_3

// 	// scalar, vector3, multivector3, pseudoscalar = 8 values
// 	int a[8] = {1,2,3,4,5,6,7,8};
// 	int b[8] = {1,2,3,4,5,6,7,8};
// 	int c[8] = {0,0,0,0,0,0,0,0};

// 	// (a[0] + a[1:3] + a[4:6] + a[7]) ( b[0] + b[1:3] + b[4:6] + b[7]);

// 	// The scalar a[0] just scales everything
// 	// a[0] ( b[0] + b[1:3] + b[4:6] + b[7]);
// 	for (int i = 0; i < 8; i += 1){
// 		c[i] = a[0] * b[i];
// 	}

// 	// Multiplication by the vector a[1:3]
// 	// does some interesting things
// 	// a[1:3] ( b[0] + b[1:3] + b[4:6] + b[7]);

// 	// a[1:3] * b[0] = vector
// 	c[1] += a[1] * b[0];
// 	c[2] += a[2] * b[0];
// 	c[3] += a[3] * b[0];

// 	// a[1:3] * b[1:3] = scalar + bivector 23 31 12
// 	// scalar
// 	c[0] += a[1] * b[1];
// 	c[0] += a[2] * b[2];
// 	c[0] += a[3] * b[3];

// 	// bivector e23 e31 e12
// 	c[4] += a[2] * b[3] - a[3] * b[2];
// 	c[5] += a[3] * b[1] - a[1] * b[3];
// 	c[6] += a[1] * b[2] - a[2] * b[1];
	
// 	// a[1:3] * b[4:6] = pseudoscalar + vector
// 	// pseudoscalar
// 	c[7] += a[1] * b[4];
// 	c[7] += a[2] * b[5];
// 	c[7] += a[3] * b[6];

// 	// vector e1 e2 e3   e23 e31 e12
// 	c[1] += -a[2] * b[3+3] + a[3] * b[2+3]; // e1
// 	c[2] += -a[3] * b[1+3] + a[1] * b[3+3]; // e2
// 	c[3] += -a[1] * b[2+3] + a[2] * b[1+3]; // e3


// 	// a[1:3] * b[7] = bivector
// 	c[4] += a[1] * b[7]; // 23
// 	c[5] += a[2] * b[7]; // 31
// 	c[6] += a[3] * b[7]; // 12


// 	printf("[%d %d %d %d %d %d %d %d]\n", c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);

// 	// a[4:6] ( b[0] + b[1:3] + b[4:6] + b[7]);
// 	// Bivector * b multivector

// 	// bivector e23 e31 e12 * 1
// 	c[4] += a[4] * b[0];
// 	c[5] += a[5] * b[0];
// 	c[6] += a[6] * b[0];

// 	// a[4:6] * b[1:3] : e23 e31 e12 * e1 e2 e3
// 	// trivector
// 	c[7] += a[4] * b[1];
// 	c[7] += a[5] * b[2];
// 	c[7] += a[6] * b[3];
// 	// vector component
// 	c[1] += - a[2+3] * b[3] + a[3+3] * b[2]; // e1
// 	c[2] += - a[3+3] * b[1] + a[1+3] * b[3]; // e2
// 	c[3] += - a[1+3] * b[2] + a[2+3] * b[1]; // e3

// 	// a[4:6] * b[4:6] = e23 e31 e12  * e23 e31 e12 
// 	// scalar
// 	c[0] += a[4] * b[4];
// 	c[0] += a[5] * b[5];
// 	c[0] += a[6] * b[6];
// 	// bivector
// 	// 2*3 e3112 e1231  -e32 + e23 = element 1
// 	// 3*1 e1223 e2312 e13 e31 -> -e31 e31   2
// 	// 1*2 e2331 e3123 = -e12 el 3
// 	c[4] += - a[2+3] * b[3] + a[3+3] * b[2]; // e23
// 	c[5] += - a[3+3] * b[1] + a[1+3] * b[3]; // e31
// 	c[6] += - a[1+3] * b[2] + a[2+3] * b[1]; // e12

// 	// a[4:6] * b[7]
// 	// bivector * pseudoscalar = -vector
// 	c[1] = - a[4] * b[7];
// 	c[2] = - a[5] * b[7];
// 	c[3] = - a[6] * b[7];




// 	return 0;

// }
