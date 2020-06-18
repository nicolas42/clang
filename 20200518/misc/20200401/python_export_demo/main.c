#include "main.h"

int test(int a)
{
	return 2*a;
}

int is_prime(int a){
	
	// int sqrta = (int) ceil(sqrt( (double) a ));

	for ( int i = 2; i < a; i++ ){
		if ( a%i == 0){
			return 0;
		}
	}
	return 1;
}
