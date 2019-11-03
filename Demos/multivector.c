#include "multivector.h"

// #define MULTIVECTOR_LENGTH 200
// void multivector_print(char *str, MULTIVECTOR *v){
// 	snprintf(str, MULTIVECTOR_LENGTH, "[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]", 
// 			v->e0, v->e1, v->e2, v->e3, v->e23, v->e31, v->e12, v->e123);
// }

void multivector_init(MULTIVECTOR *a){
	a->e0 = 0; a->e1 = 0; a->e2 = 0; a->e3 = 0; a->e23 = 0; a->e31 = 0; a->e12 = 0; a->e123 = 0; 
}

void multivector_product(MULTIVECTOR *c, MULTIVECTOR *a_arg, MULTIVECTOR *b_arg){
	MULTIVECTOR a = *a_arg;
	MULTIVECTOR b = *b_arg;
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

void multivector_rotate(MULTIVECTOR *Rab, MULTIVECTOR *v, MULTIVECTOR *a, MULTIVECTOR *b){

	MULTIVECTOR ab, ba, v2;
	multivector_init(&ab); multivector_init(&ba); multivector_init(&v2);

	multivector_product(&ab, a, b);
	multivector_product(&ba, b, a);

	multivector_product(&v2, v, &ab);
	multivector_product(Rab, &ba, &v2);
}

