// gcc lock_demo.c && ./a.out 1000
// This script has a lot of threads modifying a single global
// It can be configured to lock the modify using
	// #define FUNCTION add1
	// #define FUNCTION add1_locked

// Demo
// gcc lock_demo.c && ./a.out 1000
// launches 1000 threads

// You might have to try it multiple times to see that 
// the result doesn't always equal the number of threads
//


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define FUNCTION add1
// #define FUNCTION add1_locked

static int sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* add1_locked(void* arg)
{
	pthread_mutex_lock(&mutex);
	sum += 1;
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);

}

void* add1(void* arg)
{
	// pthread_mutex_lock(&mutex);
	sum += 1;
	// pthread_mutex_unlock(&mutex);
	pthread_exit(0);

}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <num 1> <num 2> ... <num-n>\n", argv[0]);
		exit(-1);
	}
	int num_args = atoll(argv[1]);

	// Launch threads
	pthread_t tids[num_args];
	for (int i = 0; i < num_args; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, FUNCTION, NULL);
	}

	// Wait for threads
	for (int i = 0; i < num_args; i++) {
		pthread_join(tids[i], NULL);
	}
	printf("Result is %d\n", sum);

}
