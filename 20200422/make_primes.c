#include <stdio.h>
#include "util.h"

typedef unsigned long long u64;
static FILE* file;

int file_exists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

void sig_handler(int signo)
{
  if (signo == SIGINT){
    fclose(file);
    printf("received SIGINT\n");
    exit(0);
  }
}

typedef struct primes_t {
    u64* data;
    size_t length;
    size_t allocated;
} primes_t;

int main(int argc, char** argv){

  if (signal(SIGINT, sig_handler) == SIG_ERR)
      printf("\ncan't catch SIGINT\n");


    // If primes files exist then get primes from it
    // otherwise just start with a 2 as the first prime
    primes_t primes;
    primes.data = malloc((int)1e6 * sizeof(u64));
    primes.length = 0;

    if (file_exists("primes")){
        printf("woo");
        string f = read_file("primes");
        strings s = split_destructive(f.data, "\n\r\t ");

        for (size_t i = 0; i < s.length; i++)
        {             
            printf("%s ", s.data[i]);       
            char* ptr;
            primes.data[i] = strtoll(s.data[i], &ptr, 10);
            primes.length += 1;
        }
        printf("\n");

    }

    // printf("*last prime: %llu ", primes.data[primes.length-1]);
    
    if (primes.length == 0){
        primes.data[0] = 2;
        primes.length = 1;
    }

	double t1 = get_time();

	file = fopen("primes", "a");

    u64 is_prime = 0;
    u64 a = primes.data[primes.length-1];
	for ( ; ; a++){
		is_prime = 1;
		for ( u64 i = 0; i < primes.length; i++){
			if ( a%primes.data[i] == 0){
				is_prime = 0;
				break;
			}
		}
		if (is_prime){
			primes.data[primes.length++] = a;
            fprintf(file, "%llu ", primes.data[primes.length-1]);

			// printf("%d ", a);
		}


		if (get_time()-t1 >= 1){
			t1 = get_time();
			printf("last prime: %llu\r\n", primes.data[primes.length-1]);

            // if (t1 > timeout){ break; }
		}
	}

    fclose(file);

	// for ( u64 i = 0; i < primes.length; i++){
	// 	printf("%d ", primes.data[i]);
	// }

	return 0;
}
