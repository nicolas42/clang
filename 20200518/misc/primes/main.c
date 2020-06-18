#include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
#include <time.h>
// #include <stdint.h>
#include "intarray.h"


// int is_prime(int a){
	
// 	// int sqrta = (int) ceil(sqrt( (double) a ));

// 	for ( int i = 2; i < a; i++ ){
// 		if ( a%i == 0){
// 			return 0;
// 		}
// 	}
// 	return 1;
// }

int main(){

	// INTARRAY primes;
	// intarray_init(&primes);

	int primes[1000000] = {2};
	int primes_length = 1;
	int is_prime = 0;

	clock_t t1 = 0, t2=0;

	for (int a = 2; a<1000000000; a++){
		is_prime = 1;
		for ( int i = 0; i < primes_length; i++){
			if ( a%primes[i] == 0){
				is_prime = 0;
				break;
			}
		}
		if (is_prime){
			primes[primes_length++] = a;
			// printf("%d ", a);
		}

		t2 = clock();
		if ((t2-t1)/CLOCKS_PER_SEC >= 1){
			t1 = clock();
			printf("last prime: %d\r\n ", primes[primes_length-1]);
		}
	}

	for ( int i = 0; i < primes_length; i++){
		printf("%d ", primes[i]);
	}

	return 0;
}


// int main(int argc, char **argv)
// {
// 	printf("Hello World\r\n");

// 	INTARRAY arr;
// 	intarray_init(&arr);

// 	// clock_t dt = 0;
// 	// clock_t start_time = clock();

// 	int MAX_PRIME = 1000;

//     switch (argc){
// 	case 2:
// 		MAX_PRIME = atoi(argv[1]); 
// 		break;
// 	default:
// 		// usage();
// 		printf("generate-primes [MAX_PRIME]\r\n");
// 		break;
// 	}


// 	for ( int i = 2; i < MAX_PRIME; i++ ){
// 		if ( is_prime(i) ){
// 			intarray_add(&arr, i);
// 			// dt = (clock()-start_time)/CLOCKS_PER_SEC;
// 		}
// 	}
	
// 	for (int i=0; i<arr.length; i++){
// 		printf("%d ", arr.data[i]);
// 	}


// 	return 0;
// }




