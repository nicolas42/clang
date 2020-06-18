
/*
./make; open mandelbrot.ppm 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "mandelbrot.h"

struct mandelbrot_arg
{
	double xcenter;
	double ycenter;
	double width;
	double height;
};



void usage(void){
	printf("mandelbrot [pixel_width] [pixel_height]\r\n");
}

 int main(int argc, char** argv){

    int pixel_width, pixel_height;
    double xcenter, ycenter, width, height;

    pixel_width = 1000; pixel_height = 1000;
    xcenter = 0; ycenter = 0; width = 4; height = 4;

    switch (argc){
        char* ptr;
	case 1:
		usage(); 
        printf("Making 1000x1000 mandelbrot image...\r\n");
		break;
	case 3:
		pixel_width = atoi(argv[1]); 
		pixel_height = atoi(argv[2]);
        printf("Making %dx%d mandelbrot image...\r\n", pixel_width, pixel_height);		
		break;
	case 6:
		pixel_width = atoi(argv[1]); 
		pixel_height = atoi(argv[2]);
		xcenter = strtod(argv[3], &ptr);
		ycenter = strtod(argv[4], &ptr);
		width = strtod(argv[5], &ptr);
		height = strtod(argv[5], &ptr);
        printf("Making %dx%d pixel mandelbrot image at %.2fx%.2f with size %.2fx%.2f...\r\n", pixel_width, pixel_height, xcenter, ycenter, width, height);		
		break;
	case 7:
		pixel_width = atoi(argv[1]); 
		pixel_height = atoi(argv[2]);
		xcenter = strtod(argv[3], &ptr);
		ycenter = strtod(argv[4], &ptr);
		width = strtod(argv[5], &ptr);
		height = strtod(argv[6], &ptr);
        printf("Making %dx%d pixel mandelbrot image at %.2fx%.2f with size %.2fx%.2f...\r\n", pixel_width, pixel_height, xcenter, ycenter, width, height);		
		break;
	default:
		usage(); 
		return 1;
		break;
	}
    // printf("\nargc: %d\n", argc);
    mandelbrot(pixel_width, pixel_height, xcenter, ycenter, width, height);
    
    return 0;
}

