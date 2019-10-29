#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// change of collision given a pigeon holes and b pigeons
double chance_of_collisions(double a, double b){

	double s = 1;
	
	for (double i = a; i > (a - b); i -= 1){
		s *= i / a;
		// printf("%.0f/%.0f", i, a);
	}

	return 1 - s;

}

int main(int argc, char **argv)
{

	double pigeon_holes = 365;
	double pigeons = 20;
	double P = -1;
	
	if (argc > 1) {
		pigeon_holes = atoi(argv[1]);
	}
	if (argc > 2){
		pigeons = atoi(argv[2]);
	}

	P = chance_of_collisions(pigeon_holes, pigeons);
	
	printf("Chance of collision: %f\r\n", P);
	return 0;
}
