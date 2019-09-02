#include <stdio.h>
#include <stdlib.h>
#include "mymath.h"

int main(int argc, char **argv)
{
	printf("5 * 2: %d\n", timesTwo(5));
	printf("3^2: %d\n", square(3));
	printf("42 even/odd?: %s\n", evenOddMessage(42));
	printf("Pi: %f\n", PI);

	return EXIT_SUCCESS;
}


// Every time you update a .h file you may have to do a make clean