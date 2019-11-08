#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mandelbrot.h"
#include "multivector.h"
#include "tokenize.h"
#include "count_ticks.h"
#include "primes.h"
#include "interface.h"

/* Also known as the birthday paradox */
int mymath_chance_of_collisions(double* probability, double items, double slots){

	double p = 1; // probability of no collision
	
	for (double i = slots; i > (slots - items); i -= 1){
		p *= i / slots;
		// printf("%.0f/%.0f", i, slots);
	}
	*probability = 1 - p;
	return 0;
}

int main(int argc, char **argv)
{

	// // Interface Demo
    // Library.method1();
    // Library.method2(5);
    // printf("%d\n", Library.some_value);



	// Get Arguments
	int len_args = argc-1;
	double args[len_args];
	
	for (int i = 1; i < argc; i++)
	{
		char* ptr;
		args[i-1] = strtod(argv[i], &ptr);	
	}

	for(size_t i = 0; i < len_args; ++i)
	{
		printf("%f ", args[i]);
	}


if (1){

	LIB_MULTIVECTOR m; lib_multivector_init(&m);
	// const LIB_MULTIVECTOR m = lib_multivector;

	// Multivector Rotation
	const double PI = 3.14159265359;
	double angle = PI/4;
	MULTIVECTOR v = {0,1,0,0}, a = {0,1,0,0}, b = {0,cos(angle), sin(angle)}, Rab = {0};
	m.rotate(&Rab, v, a, b);
	printf("Rotate v by twice the angle between a and b\r\n");
	m.printv(v); m.printv(a); m.printv(b); m.printv(Rab); 

}
/*

	// Collision Probability
	double probability = -1, items = 20, slots = 365;
	chance_of_collisions(&probability, items, slots);
	printf("chance-of-collision of %.0f items in %.0f positions: %f\r\n", items, slots, probability);


	// Mandelbrot Image Generation
	int pixel_width = 200, pixel_height = 200;
	double xcenter = 0, ycenter = 0, width = 4, height = 4;
    mandelbrot(pixel_width, pixel_height, xcenter, ycenter, width, height);
	printf("Making %dx%d pixel mandelbrot image at %.2fx%.2f with size %.2fx%.2f...\r\n", pixel_width, pixel_height, xcenter, ycenter, width, height);		


	// Tokenizer - read file, tokenize, then print
	char buffer[1000000];
	FILE* fp = fopen("main.c", "r");
    fread(buffer, 1000000, 1, fp);
	fclose(fp);

	int tokens[1000000];
	int tokens_length = 0;
	tokenize(tokens, &tokens_length, buffer, isnewline);

	for (int i = 0; i < tokens_length; i++){
		printf("[%s]\r\n", buffer + tokens[i]);
	}
	puts("\n");

	// Make Primes
	puts("Making primes...");
	ARRAY arr; 
	array_init(&arr);
	make_primes(&arr, 100);
	array_printf(&arr, "%.0f ");



	// Count Ticks
	puts("Counting ticks...");
	count_ticks(5);
*/
	return 0;
}


