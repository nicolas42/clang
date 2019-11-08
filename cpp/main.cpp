#include <stdio.h>
#include <math.h>
#include "multivector.h"

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


	printf("Rotate v by twice the angle between a and b\r\n\r\n");

	printf("v,a,b,Rab\r\n");
	printv(v);	printv(a);	printv(b);	printv(Rab);
	printf("\r\n");

	printf("ab,ba,tmp,Rab\r\n");
	print(ab);	print(ba);	print(tmp);	print(Rab);
	printf("\r\n");

	printf("i,j,k,ij,ijk\r\n");
	MULTIVECTOR i={0,1}, j={0,0,1}, k={0,0,0,1},jk={0}, ij={0}, ki={0}, ijk={0};
	product(&jk, j,k); 
	product(&ij, i,j);
	product(&ki, k,i);
	product(&ijk, ij,k);
	
	print(i); print(j);print(k);print(ij); print(jk); print(ki); print(ijk);
	printf("\r\n");

	return 0;
}

// int main(int argc, char **argv)
// {
// 	using namespace multivector;

// 	const double PI = 3.14159265359;
// 	double angle = PI/4;
// 	MULTIVECTOR ab = {0}, ba = {0}, Rab = {0}, tmp = {0};
// 	MULTIVECTOR v = {0,1}, a = {0,1}, b = {0,cos(angle), sin(angle)};

// 	rotate(&Rab,v,a,b);
// 	// product(&ab, a, b);
// 	// product(&ba, b, a);
// 	// product(&tmp, v, ab);
// 	// product(&Rab, ba, tmp);


// 	printf("Rotate v by twice the angle between a and b\r\n");
// 	printv(v);
// 	printv(a);
// 	printv(b);
// 	printv(Rab);

// 	return 0;
// }
