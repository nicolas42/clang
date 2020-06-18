#include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>
// #include <string.h>
#include <math.h>
#include "multivector.h"

#define MULTIVECTOR_LENGTH 200
void multivector_serialize(char *str, MULTIVECTOR *v){
	snprintf(str, MULTIVECTOR_LENGTH, "[%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f]\r\n", 
			v->e0, v->e1, v->e2, v->e3, v->e23, v->e31, v->e12, v->e123);
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



int main(int argc, char **argv)
{
	MULTIVECTOR v={0},a={0},b={0},ab={0},ba={0},Rab={0},tmp={0};
	const double PI = 3.14159265359;
	double angle = PI/4;

	// vector_copy(&a, (MULTIVECTOR*){0,1,1});
	vector_set(&v, 1,0,0);
	vector_set(&a, 1,0,0);
	vector_set(&b, cos(angle), sin(angle),0);


	multivector_product(&ab, &a, &b);
	multivector_product(&ba, &b, &a);
	multivector_product(&tmp, &v, &ab);
	multivector_product(&Rab, &ba, &tmp);


	printf("Rotate v by twice the angle between a and b\r\n");
	vector_print(&v);
	vector_print(&a);
	vector_print(&b);
	// bivector_print(&ab);
	// bivector_print(&ba);
	vector_print(&Rab);

	return 0;
}
