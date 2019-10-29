#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
// #include "multivector.h"

#define MULTIVECTOR_MAX_LENGTH 200
typedef struct {
	double e0, e1, e2, e3, e23, e31, e12, e123;
} Multivector;

void multivector_init(Multivector *a);
void multivector_product(Multivector *c, Multivector *a_arg, Multivector *b_arg);
void multivector_rotate(Multivector *Rab, Multivector *v, Multivector *a, Multivector *b);
void multivector_print(char *str, Multivector *v);

int main(int argc, char **argv)
{
	// Rotate v by twice the angle between a and b

	Multivector v = {0,1};
	Multivector a = {0,1};
	Multivector b = {0,1/sqrt(2),1/sqrt(2)};
	Multivector Rab = {0};
	multivector_rotate(&Rab, &v, &a, &b);

	char str[MULTIVECTOR_MAX_LENGTH];
	multivector_print(str, &v); puts(str);
	multivector_print(str, &Rab); puts(str);

	return 0;
}

void multivector_init(Multivector *a){
	a->e0 = 0; a->e1 = 0; a->e2 = 0; a->e3 = 0; a->e23 = 0; a->e31 = 0; a->e12 = 0; a->e123 = 0; 
}

void multivector_product(Multivector *c, Multivector *a_arg, Multivector *b_arg){
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

void multivector_rotate(Multivector *Rab, Multivector *v, Multivector *a, Multivector *b){

	// Rotate v by twice the angle between a and b
	// And scale by |ab|^2 ???

	Multivector ab, ba, v2;
	multivector_init(&ab); multivector_init(&ba); multivector_init(&v2);

	multivector_product(&ab, a, b);
	multivector_product(&ba, b, a);

	multivector_product(&v2, v, &ab);
	multivector_product(Rab, &ba, &v2);
}


void multivector_print(char *str, Multivector *v){
	snprintf(str, MULTIVECTOR_MAX_LENGTH, "[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]", 
			v->e0, v->e1, v->e2, v->e3, v->e23, v->e31, v->e12, v->e123);
}
