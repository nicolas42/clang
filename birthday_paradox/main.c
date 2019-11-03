// chance of collision given a pigeon holes and b pigeons
// usage

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double chance_of_collisions(double a, double b){

	double s = 1;
	
	for (double i = a; i > (a - b); i -= 1){
		s *= i / a;
		// printf("%.0f/%.0f", i, a);
	}

	return 1 - s;

}

void usage(void){
	printf("Usage: chance-of-collision [slots] [items]\r\n");
}

int main(int argc, char **argv)
{

	double pigeon_holes = 365;
	double pigeons = 20;
	double P = -1;
	
	switch (argc){
	case 1:
		usage(); 
		return 1;
		break;
	case 2:
		pigeons = atoi(argv[1]); 
		break;
	case 3:
		pigeons = atoi(argv[1]); 
		pigeon_holes = atoi(argv[2]);
		break;
	default:
		usage(); 
		return 1;
		break;
	}

	P = chance_of_collisions(pigeon_holes, pigeons);

	printf("chance-of-collision of %.0f items in %.0f positions: %f\r\n", pigeons, pigeon_holes, P);


	return 0;
}

