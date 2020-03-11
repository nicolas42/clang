#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
// use stride
// use long names for globals


struct image {
	int x;
	int y;
	int w; 
	int h;
	char *data;
	int stride;
};

void image_init(struct image *a, int w, int h, int stride){
	
	assert(1 <= stride && stride <= 4);

	a->w = w;
	a->h = h;
	a-> stride = stride;
	a->data = malloc(w*h*stride);

	for (size_t i = 0; i < w*h*stride; i+=stride)
	{
		// set pixel
		a->data[i] = '\0';
		a->data[i+1] = '\0';
		a->data[i+2] = '\0';
		a->data[i+3] = '\0';
	}
	
}



void image_set(struct image *a, char pixel)
{
	// set image
	for (size_t y = 0; y < a->h; y++)
	{
		for (size_t x = 0; x < a->w; x++)
		{
			for (size_t i = 0; i < a->stride; i++)
			{
				int pos = (a->w * a->stride * y) + (x * a->stride) + i;
				a->data[pos] = pixel;
			}
		}
	}
}

void image_print(struct image a)
{
	// print image
	for (size_t y = 0; y < a.h; y++)
	{
		for (size_t x = 0; x < a.w; x++)
		{	
			for (size_t i = 0; i < a.stride; i++)
			{
				int pos = (a.w * a.stride * y) + (x * a.stride) + i;
				printf("%c", a.data[pos]);
			}
			if (x < a.w - 1){ printf(","); }
		}
		printf("\n");		
	}
}

/*
render
canvas image!
image!
image!

render(struct image canvas, struct image_array images)
*/


int main(int argc, char** argv){

	printf("hello world\n");

	struct image a;
	image_init(&a, 4, 4, 4);
	image_set(&a, '0');
	image_print(a);


	return 0;
}





