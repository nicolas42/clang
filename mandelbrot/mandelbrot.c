// gcc mandelbrot.c && ./a.out
// push(){git add . && git commit -m $1 && git push}

#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


int main(int argc, char** argv){

    static unsigned char black[4] = {0, 0, 0, 255};
    static unsigned char white[4] = {255, 255, 255, 255};

    int x;
    int y;
    int WIDTH = 1000; // pixels
    int HEIGHT = 1000;

	int data_length = 4 * WIDTH * HEIGHT;
	char data[data_length];

    double xmin = -2;
    double xmax = 2;
    double ymin = -2;
    double ymax = 2;

    double xscale = WIDTH / (xmax - xmin);
    double yscale = HEIGHT / (ymax - ymin);

    double zx;
    double zxtemp;
    double zy;
    double cx;
    double cy;

    int isInSet;
    int pos;
    int STRIDE = 3;
    int i;
    int IMAX = 40;

	char* filename = "mandelbrot.ppm";


    // Open file and write header
	FILE *fp = fopen(filename, "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    // Make Black Image
    for (i = 0; i < data_length; i += STRIDE) {
		data[i + 0] = black[0];
		data[i + 1] = black[1];
		data[i + 2] = black[2];
		// data[i + 3] = black[3];
    }

    // Work out the other pixels
    for (y = 0; y < HEIGHT; y += 1) {
        for (x = 0; x < WIDTH; x += 1) {

            // image is flipped vertically. numbers go up, pixels go down
            cx = x / xscale - xmax;
            cy = y / yscale - ymax;
            zx = 0;
            zy = 0;

            isInSet = 1;
            for(i = 1; i <= IMAX; i += 1){
                zxtemp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtemp;
                if(zx * zx + zy * zy > 4){
                    isInSet = 0;
                    break;
                }
            }
            
            if (isInSet == 0) {
                pos = y * WIDTH * STRIDE + x * STRIDE;
                data[pos + 0] = white[0] * i / IMAX;
                data[pos + 1] = white[1] * i / IMAX;
                data[pos + 2] = white[2] * i / IMAX;
                // data[pos + 3] = white[3] * i / IMAX; // don't mess with opacity

				(void) fwrite(data+pos, 1, 3, fp);
				// printf(" ");
            } else {
				(void) fwrite(black, 1, 3, fp);
				// printf("*");
			}
        }
		// printf("\n");
    }

    //  ctx.putImageData(imgData, 0, 0); // Put data in canvas' 2D context

  (void) fclose(fp);
  return 0;
}


	


