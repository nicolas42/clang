#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t prime_factors(uint64_t arg)
{
	// if the input is divisible by 2 then divide it by 2 
	// if it's divisible by 3 then divide it by 3
	// and so on until the end of that number

	// variables
	// the original prime number arg
	// the divisor d

	uint64_t i = 2;

	while (arg > 1){
		// fputc('.',stdout);	
		if (arg % i == 0){
			arg /= i;
			printf("%llu ", i);
		} else {
			i++;
		}
	}

	return 0;
}

int main(int argc, char** argv){

	uint64_t arg = 999;
	char* ptr;
	if (argc > 1){
		arg = strtoll(argv[1], &ptr, 10);
	}
	prime_factors(arg);
	return 0;
}
