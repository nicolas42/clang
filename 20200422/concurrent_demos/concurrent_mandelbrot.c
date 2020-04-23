#ifndef MANDELBROT_H
#define MANDELBROT_H

// Draw a black and white mandelbrot image in file mandelbrot.ppm
// usage: mandelbrot(pixel_width, pixel_height, xcenter, ycenter, width, height);

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pixel_width;
    int pixel_height;
    double xcenter;
    double ycenter;
    double width;
    double height;
    int ystart;
    int yend;
} mandelbrot_arg;

int mandelbrot(void* arg);
void mandelbrot_usage(void);
int mandelbrot_main(int argc, char** argv);



int mandelbrot( void* arg)
{

    mandelbrot_arg a = *(mandelbrot_arg*) arg;

    int pixel_width = a.pixel_width;
    int pixel_height = a.pixel_height;
    double xcenter = a.xcenter;
    double ycenter = a.ycenter;
    double width = a.width;
    double height = a.height;
    int ystart = a.ystart;
    int yend = a.yend;

    // to see full image: mandelbrot(1000,1000,0,0,4,4);

    // center, width
    // double xcenter,ycenter, width, height;
    double xmin, xmax, ymin, ymax;

    // xcenter = 0; ycenter = 0; width = 4; height = 4;
    xmin = xcenter - width/2;
    xmax = xcenter + width/2;
    ymin = ycenter - height/2;
    ymax = ycenter + height/2;

    const unsigned char black[4] = {0, 0, 0, 255};
    const unsigned char white[4] = {255, 255, 255, 255};

    // length per pixel
    const double width_per_pixel = (xmax - xmin) / pixel_width;
    const double height_per_pixel = (ymax - ymin) / pixel_height;
    
    // Open file and write header
	char* filename = "mandelbrot.ppm";
	FILE *fp = fopen(filename, "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", pixel_width, pixel_height);

    for (int y = ystart; y <= yend ; y += 1) {
        for (int x = 0; x < pixel_width; x += 1) {

            double zx, zxtmp, zy, cx, cy;
            int is_in_set, stride, i, imax;

            stride = 3;
            imax = 40;

            // image is flipped vertically
            cx = x * width_per_pixel - xmax;
            cy = y * height_per_pixel - ymax;
            zx = 0;
            zy = 0;
            is_in_set = 1;

            for(i = 1; i <= imax; i += 1){
                zxtmp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtmp;
                if(zx * zx + zy * zy > 4){
                    is_in_set = 0;
                    break;
                }
            }
            
            if (is_in_set) {
				fwrite(black, 1, 3, fp);
				// printf("*");
            } else {
				fputc(white[0] * i / imax, fp);
				fputc(white[1] * i / imax, fp);
				fputc(white[2] * i / imax, fp);
				// printf(" ");
			}
        }
		// printf("\n");
    }

  (void) fclose(fp);
  return 0;
}

int main(int argc, char** argv){

    int pixel_width, pixel_height;
    double xcenter, ycenter, width, height;

    pixel_width = 1000; pixel_height = 1000;
    xcenter = 0; ycenter = 0; width = 4; height = 4;

    mandelbrot_arg a;

    a.pixel_width = pixel_width;
    a.pixel_height = pixel_height;
    a.xcenter = xcenter;
    a.ycenter = ycenter;
    a.width = width;
    a.height = height;
    a.ystart = 0;
    a.yend = pixel_height;
    
    // mandelbrot(a);





	// thread_arg targs[nargs];
	// pthread_t tids[nargs];

	// for (int i = 0; i < nargs; i++) {

	// 	targs[i].arg = atoll(argv[i + 1]);
	// 	pthread_attr_t attr;
	// 	pthread_attr_init(&attr);

	// 	pthread_create(&tids[i], &attr, thread_function, &targs[i]);
	// }

	// // Wait for threads
	// for (size_t i = 0; i < nargs; i++) {
    // // for (int i = nargs-1; i >= 0 ; i -= 1 ){
	// 	pthread_join(tids[i], NULL);
    //     printf("time: %.3f ", get_time() - t1 );
    //     printf("thread %lu. factorial %llu is %llu\n", i, targs[i].arg, targs[i].res);
        
	// }






    return 0;
}


#endif

