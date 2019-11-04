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

void multivector_print(MULTIVECTOR* v){
	printf("[%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f]\r\n", 
			v->e0, v->e1, v->e2, v->e3, v->e23, v->e31, v->e12, v->e123);	
}

void vector_print(MULTIVECTOR* v){
	printf("[%.3f %.3f %.3f]\r\n", v->e1, v->e2, v->e3);	
}

void bivector_print(MULTIVECTOR* v){
	printf("[%.3f %.3f %.3f]\r\n", v->e23, v->e31, v->e12);	
}

void vector_set(MULTIVECTOR *a, double v1, double v2, double v3){
	a->e1 = v1; a->e2 = v2; a->e3 = v3;
}

void vector_copy(MULTIVECTOR *a, MULTIVECTOR* b){
	a->e1 = b->e1; a->e2 = b->e2; a->e3 = b->e3; 
}




// #include <stdio.h>
// // #include <stdlib.h>
// // #include <assert.h>
// // #include <string.h>
// #include <math.h>
// #include "multivector.h"

// #define MULTIVECTOR_LENGTH 200
// void multivector_serialize(char *str, MULTIVECTOR *v){
// 	snprintf(str, MULTIVECTOR_LENGTH, "[%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f]\r\n", 
// 			v->e0, v->e1, v->e2, v->e3, v->e23, v->e31, v->e12, v->e123);
// }

// void multivector_print(MULTIVECTOR* v){
// 	printf("[%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f]\r\n", 
// 			v->e0, v->e1, v->e2, v->e3, v->e23, v->e31, v->e12, v->e123);	
// }

// void vector_print(MULTIVECTOR* v){
// 	printf("[%.3f %.3f %.3f]\r\n", v->e1, v->e2, v->e3);	
// }

// void bivector_print(MULTIVECTOR* v){
// 	printf("[%.3f %.3f %.3f]\r\n", v->e23, v->e31, v->e12);	
// }

// void vector_set(MULTIVECTOR *a, double v1, double v2, double v3){
// 	a->e1 = v1; a->e2 = v2; a->e3 = v3;
// }

// void vector_copy(MULTIVECTOR *a, MULTIVECTOR* b){
// 	a->e1 = b->e1; a->e2 = b->e2; a->e3 = b->e3; 
// }



// int main(int argc, char **argv)
// {
// 	MULTIVECTOR v={0},a={0},b={0},ab={0},ba={0},Rab={0},tmp={0};
// 	const double PI = 3.14159265359;
// 	double angle = PI/4;

// 	// vector_copy(&a, (MULTIVECTOR*){0,1,1});
// 	vector_set(&v, 1,0,0);
// 	vector_set(&a, 1,0,0);
// 	vector_set(&b, cos(angle), sin(angle),0);


// 	multivector_product(&ab, &a, &b);
// 	multivector_product(&ba, &b, &a);
// 	multivector_product(&tmp, &v, &ab);
// 	multivector_product(&Rab, &ba, &tmp);


// 	printf("Rotate v by twice the angle between a and b\r\n");
// 	vector_print(&v);
// 	vector_print(&a);
// 	vector_print(&b);
// 	// bivector_print(&ab);
// 	// bivector_print(&ba);
// 	vector_print(&Rab);

// 	return 0;
// }
