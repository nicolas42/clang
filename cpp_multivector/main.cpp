#include <stdio.h>
#include <math.h>
#include "multivector.h"

int main(int argc, char **argv)
{
	using namespace multivector;

	const double PI = 3.14159265359;
	double angle = PI/4;
	MULTIVECTOR ab = {0}, ba = {0}, Rab = {0}, tmp = {0};
	MULTIVECTOR v = {0,1}, a = {0,1}, b = {0,cos(angle), sin(angle)};

	rotate(&Rab,v,a,b);
	// product(&ab, a, b);
	// product(&ba, b, a);
	// product(&tmp, v, ab);
	// product(&Rab, ba, tmp);


	printf("Rotate v by twice the angle between a and b\r\n");
	printv(v);
	printv(a);
	printv(b);
	printv(Rab);

	return 0;
}
