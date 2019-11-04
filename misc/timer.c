#include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
#include <time.h>
// #include <stdint.h>
#include "intarray.h"

int main(){

	clock_t t1 = 0, t2 = 0;
	
	t1 = clock();

	while(1){
		t2 = clock();

		if ((t2 - t1)/CLOCKS_PER_SEC >= 1){
			t1 = clock();
			puts("WOW");
		}
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




