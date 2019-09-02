// Demo
// gcc concurrent_factorial.c && ./a.out 1 2 3 4 5 6 7

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct factorial_struct {
	long long limit;
	long long answer;
};

// Thread function to generate sum of 0 to N
void* factorial(void* arg)
{
	struct factorial_struct *arg_struct =
			(struct factorial_struct*) arg;

	long long sum = 1;
	for (long long i = 1; i <= arg_struct->limit; i++) {
		sum *= i;
	}

	arg_struct->answer = sum;

	pthread_exit(0);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <num 1> <num 2> ... <num-n>\n", argv[0]);
		exit(-1);
	}
	int num_args = argc - 1;

	struct factorial_struct args[num_args];

	// Launch thread
	pthread_t tids[num_args];
	for (int i = 0; i < num_args; i++) {
		args[i].limit = atoll(argv[i + 1]);

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, factorial, &args[i]);
	}

	// Wait until thread is done its work
	for (int i = 0; i < num_args; i++) {
		pthread_join(tids[i], NULL);
		printf("Sum for thread %d is %lld\n",
				i, args[i].answer);
	}
}
