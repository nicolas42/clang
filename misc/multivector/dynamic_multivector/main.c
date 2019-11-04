#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double *garbage[1000];
static int garbage_length = 0;

double* mul(double *a, double *b){
	
	double *c = malloc(8 * sizeof(*c));
	garbage[garbage_length++] = c;

	c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3] - a[4]*b[4] - a[5]*b[5] - a[6]*b[6] - a[7]*b[7];

	c[1] = a[0]*b[1] + a[1]*b[0] - a[2]*b[6] + a[6]*b[2] + a[3]*b[5] - a[5]*b[3] + a[7]*b[4] + a[4]*b[7];
	c[2] = a[0]*b[2] + a[2]*b[0] + a[1]*b[6] - a[6]*b[1] - a[3]*b[4] + a[4]*b[3] - a[7]*b[5] - a[5]*b[7];
	c[3] = a[0]*b[3] + a[3]*b[0] - a[1]*b[5] + a[5]*b[1] + a[2]*b[4] - a[4]*b[2] + a[7]*b[6] + a[6]*b[7];

	c[4] = a[4]*b[0] + a[0]*b[4] + a[2]*b[3] - a[3]*b[2] + a[6]*b[5] - a[5]*b[6] + a[7]*b[1] + a[1]*b[7];
	c[5] = a[5]*b[0] + a[0]*b[5] + a[3]*b[1] - a[1]*b[3] + a[4]*b[6] - a[6]*b[4] + a[7]*b[2] + a[2]*b[7];
	c[6] = a[6]*b[0] + a[0]*b[6] + a[1]*b[2] - a[2]*b[1] + a[5]*b[4] - a[4]*b[5] + a[7]*b[3] + a[3]*b[7];

	c[7] = a[0]*b[7] + a[7]*b[0] + a[1]*b[4] + a[4]*b[1] + a[2]*b[5] + a[5]*b[2] + a[3]*b[6] + a[6]*b[3];
	
	return c;
}




int main(int argc, char **argv)
{
	double v[8] = {0,1}; 
	double a[8] = {0,1}; 
	double b[8] = {0,1/sqrt(2), 1/sqrt(2)};
	double *c;
	int i;


	c = mul(b, mul(a, mul(v, mul(a, b))));

	printf("[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]\n", 
			c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);

	for (i = 0; i < garbage_length; i += 1){
		free(garbage[i]);
	}
	return 0;
}

// make_vector(&v, 1,0,0);
// make_bivector(&v, 1,0,0);
// make_complex(&v,1,1);
// make_quaternion(&v,1,2,3,4);
// make_scalar(&v,1);
// make_four_vector(&v,1,2,3,4);
