#include <stdio.h>

int prime_factors(int p)
{
	// if the input is divisible by 2 then divide it by 2 
	// if it's divisible by 3 then divide it by 3
	// and so on until the end of that number

	// variables
	// the original prime number p
	// the divisor d

	int d = 2;

	while (p > 1){
		if (p % d == 0){
			p = p / d;
			printf("%d ", d);
		} else {
			d++;
		}
	}

	return 0;
}

int main(){
	prime_factors(987);
	return 0;
}
