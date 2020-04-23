// gcc lock_demo.c && ./a.out 1000
// This script has a lot of threads modifying a single global
// It can be configured to lock the modify using
	// #define FUNCTION thread_proc
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
#include <string.h>

#define num_threads 3
#define num_iterations 5000000

static int result = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_proc(void* arg)
{
    for (size_t i = 0; i < num_iterations; i++)
    {
        // pthread_mutex_lock(&mutex);
        result += 1;
        // pthread_mutex_unlock(&mutex);
    }
     
	pthread_exit(0);

}

int main(void)
{

    result = 0;
    // Launch threads
    pthread_t tids[num_threads];
    for (int i = 0; i < num_threads; i++) {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, thread_proc, NULL);
    }

    // Wait for threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(tids[i], NULL);
    }

    printf("Result is %d\n", result);

    int correct = num_threads * num_iterations;
    if (result == correct){
        printf("CORRECT!\n");
    } else {
        printf("INCORRECT!\n");
    }

}
