// gcc -Wall -pedantic test.c && ./a.out

/* I'm going to try to implement the wedge and dot products here */
#include <stdio.h>
#include <stdlib.h>

int dot(int *a, int *b){
	int c = 0;
	int i;
	for (i = 0; i < 3; i += 1){
		c += a[i] * b[i];
	}
	return c;
}

int* wedge(int *a, int *b){

	int *c = malloc( 3 * sizeof(*c));
	int i;
	for (i = 0; i < 3; i += 1){
		c[i] = (a[i] * b[i]);
	}
	return c;
}

void vprint(int *a){
	printf("[%d %d %d]", a[0], a[1], a[2]);
}

// typedef struct {
// 	int scalar;
// 	int vector[3];
// 	int multivector[3];
// 	int pseudoscalar;
// } MultiVector;

// void MultiVector_init(MultiVector* a){
// 	a->scalar = 0;
// 	int i;
// 	for (i = 0; i < 3; i += 1){
// 		a->vector[i] = 0;
// 		a->multivector[i] = 0;
// 	}
// 	a->pseudoscalar = 0;
// }

// void mul(MultiVector* a, MultiVector* b){
	
// 	MultiVector* c = malloc(sizeof (*c));
// 	MultiVector_init(c);

// 	// Multiply by b->scalar
// 	c->scalar = a->scalar * b->scalar;
// 	for (int i = 0; i < 3; i += 1){
// 		c->vector[i] = a->vector[i] * b->scalar;
// 		c->multivector[i] = a->multivector[i] * b->scalar;
// 	}
// 	c->pseudoscalar = a->pseudoscalar * b->scalar;

// }

int main(int argc, char **argv)
{

/*
	// make some vectors
	int v1[3] = {1,2,3};
	int v2[3] = {1,2,3};

	int a = dot(v1,v2);
	int *c = wedge(v1,v2);

	printf("dot: %d\n", a);
	vprint(c);
	printf("\n");
*/


/*
if (1){
	// Geometric Product
	int c[3][3];
	int a[3] = {1,2,3};
	int b[3] = {1,2,3};

	int i, j;
	for (i = 0; i < 3; i += 1){
		for (j = 0; j < 3; j += 1){
			c[i][j] = a[i] * b[j];
		}
	}

	int dot = 0;
	for (i = 0; i < 3; i += 1){
		dot += c[i][i];
	}

	int wedge[3];
	int k = 0;
	for (i = 0; i < 3; i += 1){
		for (j = 0; j < i; j += 1){
			// k++ seems like a bug waiting to happen
			wedge[k++] = c[i][j] - c[j][i]; 
			// printf(".");
		}
	}
	printf("dot: %d\n", dot);
	printf("wedge: [%d %d %d]\n", wedge[0], wedge[1], wedge[2]);

}
*/

	// Multiply two multivectors
	int a[8] = {1,2,3,4,5,6,7,8};
	int b[8] = {1,2,3,4,5,6,7,8};
	int c[8] = {0,0,0,0,0,0,0,0};

	// c = a * b;

	// Multiplication by a[0] the scalar just scales everything
	for (int i = 0; i < 8; i += 1){
		c[i] = b[i] * a[i];
	}

	// Multiplication by the vector a[1:3]
	// a[1:3] ( b[0] + b[1:3] + b[4:6] + b[7]);
	// Note: Bivectors have dimensions e_23 e_31 e_12

	// a[1:3] * b[0] = vector
	c[1] += b[0] * a[1];
	c[2] += b[0] * a[2];
	c[3] += b[0] * a[3];

	// a[1:3] * b[1:3] = scalar + multivector 23 31 12
	c[0] += b[1] * a[1];
	c[0] += b[2] * a[2];
	c[0] += b[3] * a[3];

	c[4] += b[2] * a[3] - b[3] * a[2];
	c[5] += b[3] * a[1] - b[1] * a[3];
	c[6] += b[1] * a[2] - b[2] * a[1];
	
	// a[1:3] * b[4:6] = pseudoscalar + vector
	c[7] += b[4] * a[1];
	c[7] += b[5] * a[2];
	c[7] += b[6] * a[3];

	c[1] += -a[2] * b[3+3] + a[3] * b[2+3]; // 23
	c[2] += -a[3] * b[1+3] + a[1] * b[3+3]; // 31
	c[3] += -a[1] * b[2+3] + a[2] * b[1+3]; // 12


	// a[1:3] * b[7] = multivector
	c[4] += a[1] * b[7]; // 23
	c[5] += a[2] * b[7]; // 31
	c[6] += a[3] * b[7]; // 12






	return 0;

}
