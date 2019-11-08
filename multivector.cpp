/*g++ multivector.cpp && ./a.out */

#include <stdio.h>
#include <math.h>
// #include "multivector.h"

namespace multivector {

	typedef struct {
		double e0, e1, e2, e3, e23, e31, e12, e123;
	} MULTIVECTOR;

	void init(MULTIVECTOR *a){
		a->e0 = 0; a->e1 = 0; a->e2 = 0; a->e3 = 0; a->e23 = 0; a->e31 = 0; a->e12 = 0; a->e123 = 0; 
	}

	void product(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b){
		c->e0 	= a.e0*b.e0 	+ a.e1*b.e1 	+ a.e2*b.e2 	+ a.e3*b.e3 	- a.e23*b.e23 	- a.e31*b.e31 	- a.e12*b.e12 	- a.e123*b.e123;
		c->e1 	= a.e0*b.e1 	+ a.e1*b.e0 	- a.e2*b.e12 	+ a.e12*b.e2 	+ a.e3*b.e31 	- a.e31*b.e3 	- a.e123*b.e23 	+ a.e23*b.e123;
		c->e2 	= a.e0*b.e2 	+ a.e2*b.e0 	+ a.e1*b.e12 	- a.e12*b.e1 	- a.e3*b.e23 	+ a.e23*b.e3 	- a.e123*b.e31 	- a.e31*b.e123;
		c->e3 	= a.e0*b.e3 	+ a.e3*b.e0 	- a.e1*b.e31 	+ a.e31*b.e1 	+ a.e2*b.e23 	- a.e23*b.e2 	- a.e123*b.e12 	- a.e12*b.e123;
		c->e23 	= a.e23*b.e0 	+ a.e0*b.e23 	+ a.e2*b.e3 	- a.e3*b.e2 	+ a.e12*b.e31 	- a.e31*b.e12 	+ a.e123*b.e1 	+ a.e1*b.e123;
		c->e31 	= a.e31*b.e0 	+ a.e0*b.e31 	+ a.e3*b.e1 	- a.e1*b.e3 	+ a.e23*b.e12 	- a.e12*b.e23 	+ a.e123*b.e2 	+ a.e2*b.e123;
		c->e12 	= a.e12*b.e0 	+ a.e0*b.e12 	+ a.e1*b.e2 	- a.e2*b.e1 	+ a.e31*b.e23 	- a.e23*b.e31 	+ a.e123*b.e3 	+ a.e3*b.e123;
		c->e123	= a.e0*b.e123 	+ a.e123*b.e0 	+ a.e1*b.e23 	+ a.e23*b.e1 	+ a.e2*b.e31 	+ a.e31*b.e2 	+ a.e3*b.e12 	+ a.e12*b.e3;
	}

	void rotate(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b){

		MULTIVECTOR ab, ba, v2;
		init(&ab); init(&ba); init(&v2);

		product(&ab, a, b);
		product(&ba, b, a);
		product(&v2, v, ab);
		product(Rab, ba, v2);
	}

	void print(MULTIVECTOR v){
		printf("[%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]\r\n", 
				v.e0, v.e1, v.e2, v.e3, v.e23, v.e31, v.e12, v.e123);	
	}

	void printv(MULTIVECTOR v){
		printf("[%.2f %.2f %.2f]\r\n", v.e1, v.e2, v.e3);	
	}

	char* str(char* buf, MULTIVECTOR v){
		sprintf(buf, "[%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]\r\n", 
				v.e0, v.e1, v.e2, v.e3, v.e23, v.e31, v.e12, v.e123);	
				
		return buf;
	}

}

int main(int argc, char **argv)
{
	using namespace multivector;

	// Allocate, initialize to zero, define constants
	const double PI = 3.14159265359;
	double angle = PI/4;
	MULTIVECTOR ab = {0}, ba = {0}, Rab = {0}, tmp = {0};
	
	// arguments
	MULTIVECTOR v = {0,1}, a = {0,1}, b = {0,cos(angle), sin(angle)};
	rotate(&Rab,v,a,b);
	
	product(&ab, a, b);
	product(&ba, b, a);
	product(&tmp, v, ab);
	product(&Rab, ba, tmp);


	printf("Rotate v by twice the angle between a and b\r\n");
	puts("v,a,b,Rab");
	print(v);
	print(a);
	print(b);
	print(Rab);
	
	printf("\r\n\r\n");
	printf("ab,ba,tmp,Rab,ij,ijk\r\n");
	print(ab);
	print(ba);
	print(tmp);
	print(Rab);

	MULTIVECTOR i={0,1}, j={0,0,1}, k={0,0,0,1},ij={0}, ijk={0};	
	product(&ij, i,j);
	product(&ijk, ij,k);
	
	char b1[200], b2[200];
	printf("%s %s\r\n", str(b1,ij), str(b2,ijk));
	

	return 0;
}
