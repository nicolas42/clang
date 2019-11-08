/*g++ multivector.cpp && ./a.out */

// #include <stdio.h>
// #include <math.h>
#include "multivector.h"

// typedef struct {
// 	double e0, x, y, z, yz, zy, xy, xyz;
// } MULTIVECTOR;

const LIB_MULTIVECTOR lib_multivector = {
	.init = multivector_init,
	.product = multivector_product,
	.rotate = multivector_rotate,
	.print = multivector_print,
	.printv = multivector_printv,
	.str = multivector_str
};

void lib_multivector_init(LIB_MULTIVECTOR *a){
	a->init = multivector_init;
	a->product = multivector_product;
	a->rotate = multivector_rotate;
	a->print = multivector_print;
	a->printv = multivector_printv;
	a->str = multivector_str;
}

void multivector_init(MULTIVECTOR *a){
	a->e0 = 0; a->x = 0; a->y = 0; a->z = 0; a->yz = 0; a->zy = 0; a->xy = 0; a->xyz = 0; 
}

void multivector_product(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b){
	c->e0 	= a.e0*b.e0 	+ a.x*b.x 	+ a.y*b.y 	+ a.z*b.z 	- a.yz*b.yz 	- a.zy*b.zy 	- a.xy*b.xy 	- a.xyz*b.xyz;
	c->x 	= a.e0*b.x 	+ a.x*b.e0 	- a.y*b.xy 	+ a.xy*b.y 	+ a.z*b.zy 	- a.zy*b.z 	- a.xyz*b.yz 	+ a.yz*b.xyz;
	c->y 	= a.e0*b.y 	+ a.y*b.e0 	+ a.x*b.xy 	- a.xy*b.x 	- a.z*b.yz 	+ a.yz*b.z 	- a.xyz*b.zy 	- a.zy*b.xyz;
	c->z 	= a.e0*b.z 	+ a.z*b.e0 	- a.x*b.zy 	+ a.zy*b.x 	+ a.y*b.yz 	- a.yz*b.y 	- a.xyz*b.xy 	- a.xy*b.xyz;
	c->yz 	= a.yz*b.e0 	+ a.e0*b.yz 	+ a.y*b.z 	- a.z*b.y 	+ a.xy*b.zy 	- a.zy*b.xy 	+ a.xyz*b.x 	+ a.x*b.xyz;
	c->zy 	= a.zy*b.e0 	+ a.e0*b.zy 	+ a.z*b.x 	- a.x*b.z 	+ a.yz*b.xy 	- a.xy*b.yz 	+ a.xyz*b.y 	+ a.y*b.xyz;
	c->xy 	= a.xy*b.e0 	+ a.e0*b.xy 	+ a.x*b.y 	- a.y*b.x 	+ a.zy*b.yz 	- a.yz*b.zy 	+ a.xyz*b.z 	+ a.z*b.xyz;
	c->xyz	= a.e0*b.xyz 	+ a.xyz*b.e0 	+ a.x*b.yz 	+ a.yz*b.x 	+ a.y*b.zy 	+ a.zy*b.y 	+ a.z*b.xy 	+ a.xy*b.z;
}

void multivector_rotate(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b){

	MULTIVECTOR ab, ba, v2;
	multivector_init(&ab); multivector_init(&ba); multivector_init(&v2);

	multivector_product(&ab, a, b);
	multivector_product(&ba, b, a);
	multivector_product(&v2, v, ab);
	multivector_product(Rab, ba, v2);
}

void multivector_print(MULTIVECTOR v){
	printf("[%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]\r\n", 
			v.e0, v.x, v.y, v.z, v.yz, v.zy, v.xy, v.xyz);	
}

void multivector_printv(MULTIVECTOR v){
	printf("[%.2f %.2f %.2f]\r\n", v.x, v.y, v.z);	
}

char* multivector_str(char* buf, MULTIVECTOR v){
	sprintf(buf, "[%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]\r\n", 
			v.e0, v.x, v.y, v.z, v.yz, v.zy, v.xy, v.xyz);	
			
	return buf;
}

// int main(int argc, char **argv)
// {
// 	using namespace multivector;

// 	// Allocate, initialize to zero, define constants
// 	const double PI = 3.14159265359;
// 	double angle = PI/4;
// 	MULTIVECTOR ab = {0}, ba = {0}, Rab = {0}, tmp = {0};
	
// 	// arguments
// 	MULTIVECTOR v = {0,1}, a = {0,1}, b = {0,cos(angle), sin(angle)};
// 	multivector_rotate(&Rab,v,a,b);
	
// 	multivector_product(&ab, a, b);
// 	multivector_product(&ba, b, a);
// 	multivector_product(&tmp, v, ab);
// 	multivector_product(&Rab, ba, tmp);


// 	printf("Rotate v by twice the angle between a and b\r\n\r\n");

// 	printf("v,a,b,Rab\r\n");
// 	multivector_printv(v);	multivector_printv(a);	multivector_printv(b);	multivector_printv(Rab);
// 	printf("\r\n");

// 	printf("ab,ba,tmp,Rab\r\n");
// 	multivector_print(ab);	multivector_print(ba);	multivector_print(tmp);	multivector_print(Rab);
// 	printf("\r\n");

// 	printf("i,j,k,ij,ijk\r\n");
// 	MULTIVECTOR i={0,1}, j={0,0,1}, k={0,0,0,1},jk={0}, ij={0}, ki={0}, ijk={0};
// 	multivector_product(&jk, j,k); 
// 	multivector_product(&ij, i,j);
// 	multivector_product(&ki, k,i);
// 	multivector_product(&ijk, ij,k);
	
// 	multivector_print(i); multivector_print(j);multivector_print(k);multivector_print(ij); multivector_print(jk); multivector_print(ki); multivector_print(ijk);
// 	printf("\r\n");

// 	return 0;
// }
