#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mandelbrot.h"

int main(int argc, char **argv)
{

	// Make Mandelbrot Image
	int pixel_width = 200, pixel_height = 200;
	double xcenter = 0, ycenter = 0, width = 4, height = 4;
    mandelbrot(pixel_width, pixel_height, xcenter, ycenter, width, height);
	printf("Making %dx%d pixel mandelbrot image at %.2fx%.2f with size %.2fx%.2f...\r\n", pixel_width, pixel_height, xcenter, ycenter, width, height);		
	printf("\r\n");

	return 0;
}


