/* gcc -std=c++11 -c *.cpp && gcc -std=c99 -c *.c && gcc *.o && ./a.out */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mandelbrot.h"
#include "tokenize.h"
#include "count_ticks.h"
#include "primes.h"
#include "errno.h"
}

#include "multivector.h"

/* Also known as the birthday paradox */
int chance_of_collisions(double* probability, double items, double slots){

	double p = 1; // probability of no collision
	
	for (double i = slots; i > (slots - items); i -= 1){
		p *= i / slots;
		// printf("%.0f/%.0f", i, slots);
	}
	*probability = 1 - p;
	return 0;
}

double min(double a, double b){
	if (a < b){
		return a;
	} else {
		return b;
	}
}

int main(int argc, char **argv)
{

	// Get Arguments
	int len_args = argc-1;
	double* args = (double*)malloc(len_args * sizeof (double));

	for (int i = 1; i < argc; i++)
	{
		char* ptr;
		args[i-1] = strtod(argv[i], &ptr);	
	}
	printf("Arguments\r\n");
	for(size_t i = 0; i < len_args; ++i)
	{
		printf("%f ", args[i]);
	}
	printf("\r\n");

	// Rotate multivector
	const double PI = 3.14159265359;
	double angle = PI/4;
	MULTIVECTOR v = {0,1,0,0}, a = {0,1,0,0}, b = {0,cos(angle), sin(angle)}, Rab = {0};	
	multivector.rotate(&Rab, v, a, b);
	printf("Rotate v by twice the angle between a and b\r\n");
	multivector.printv(v); multivector.printv(a); multivector.printv(b); multivector.printv(Rab); 
	printf("\r\n");



	// Calculate the probability of a collision (birthday paradox)
	double probability = -1, items = 20, slots = 365;
	chance_of_collisions(&probability, items, slots);
	printf("chance-of-collision of %.0f items in %.0f positions: %f\r\n", items, slots, probability);
	printf("\r\n");


	// Make Mandelbrot Image
	int pixel_width = 400, pixel_height = 400;
	double xcenter = 0, ycenter = 0, width = 4, height = 4;
    mandelbrot(pixel_width, pixel_height, xcenter, ycenter, width, height);
	printf("Making %dx%d pixel mandelbrot image at %.2fx%.2f with size %.2fx%.2f...\r\n", pixel_width, pixel_height, xcenter, ycenter, width, height);		
	printf("\r\n");



	// Tokenizer
	// read file
	char buffer[1000000];
	FILE* fp;
	fp = fopen("main.cpp", "r");
	// if (!fp){
	// 	printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
	// 	exit(1);
	// }
    fread(buffer, 1000000, 1, fp);
	fclose(fp);
	
	// make tokens
	int tokens[1000000];
	int len_tokens = 0;
	tokenize(tokens, &len_tokens, buffer, isspace);
		// print tokens
	for (int i = 0; i < min(10, len_tokens); i++){
		printf("[%s] ", buffer + tokens[i]);
	}
	printf("\r\n");



	// Make Primes
	puts("Making primes...");
	ARRAY arr; 
	array_init(&arr);
	make_primes(&arr, 100);
	array_printf(&arr, (char*)"%.0f ");
	printf("\r\n");


/*
	// Count Ticks
	puts("Counting ticks...");
	count_ticks(5);
	printf("\r\n");
*/

	return 0;
}


