// gcc mandelbrot.c && ./a.out

#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


int main(int argc, char** argv){

    char black[4] = {0, 0, 0, 255};
    char white[4] = {255, 255, 255, 255};
    int x;
    int y;
    int width = 100; // pixels
    int height = 100;
    // var canvas = document.querySelector("#canvas");
    // canvas.height = height;
    // canvas.width = width;

    // get the image from the context - image: {width, height, data}
    // var ctx = canvas.getContext("2d");
    // var imgData = ctx.getImageData(0, 0, width, height);
    // var data = imgData.data;

	int data_length = 4 * width * height;
	char data[data_length];

    double xmin = -2;
    double xmax = 2;
    double ymin = -2;
    double ymax = 2;

    double xscale = width / (xmax - xmin);
    double yscale = height / (ymax - ymin);

    double zx;
    double zxtemp;
    double zy;
    double cx;
    double cy;

    int isInSet;
    int pos;
    int stride = 4; // 4 bytes per pixel
    int i;
    int imax = 40;

    // Make Black Image
    for (i = 0; i < data_length; i += stride) {
		data[i + 0] = black[0];
		data[i + 1] = black[1];
		data[i + 2] = black[2];
		data[i + 3] = black[3];
    }

    // Work out the other pixels
    for (y = 0; y < height; y += 1) {
        for (x = 0; x < width; x += 1) {

            // image is flipped vertically. numbers go up, pixels go down
            cx = x / xscale - xmax;
            cy = y / yscale - ymax;
            zx = 0;
            zy = 0;

            isInSet = 1;
            for(i = 1; i <= imax; i += 1){
                zxtemp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtemp;
                if(zx * zx + zy * zy > 4){
                    isInSet = 0;
                    break;
                }
            }
            
            if (isInSet == 0) {
                pos = y * width * stride + x * stride;
                data[pos + 0] = white[0] * i / imax;
                data[pos + 1] = white[1] * i / imax;
                data[pos + 2] = white[2] * i / imax;
                // data[pos + 3] = white[3] * i / imax; // don't mess with opacity

				printf(" ");
            } else {
				printf("*");
			}
        }
		printf("\n");
    }

    //  ctx.putImageData(imgData, 0, 0); // Put data in canvas' 2D context

	return 0;
}


	


