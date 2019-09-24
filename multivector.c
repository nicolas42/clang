// gcc -Wall -pedantic multivector.c && ./a.out

#include <stdio.h>
#include <stdlib.h>

// Test Multiplying two 3 dimensional multivectors
// https://www.euclideanspace.com/maths/algebra/clifford/d3/arithmetic/index.htm
int main(int argc, char **argv)
{
	// scalar, vector3, bivector3, pseudoscalar
	// bivector has components e23 e31 e12 
	// pseudoscalar has component e123
	// double a[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
	// double b[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
	double a[8] = {1, 0, 0, 0, 1, 0, 0, 0};
	double b[8] = {1, 0, 0, 0, 1, 0, 0, 0};
	double c[8] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};

	c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3] - a[4]*b[4] - a[5]*b[5] - a[6]*b[6] - a[7]*b[7];
	c[1] = a[0]*b[2] + a[2]*b[0] - a[2]*b[6] + a[6]*b[2] + a[3]*b[5] - a[5]*b[3] + a[7]*b[4] + a[4]*b[7];
	c[2] = a[0]*b[2] + a[2]*b[0] + a[1]*b[6] - a[6]*b[1] - a[3]*b[4] + a[4]*b[3] - a[7]*b[5] - a[5]*b[7];
	c[3] = a[0]*b[3] + a[3]*b[0] - a[1]*b[5] + a[5]*b[1] + a[2]*b[4] - a[4]*b[3] + a[7]*b[4] + a[4]*b[7];
	c[4] = a[4]*b[0] + a[0]*b[4] + a[2]*b[3] - a[3]*b[2] + a[6]*b[5] - a[5]*b[6] + a[7]*b[1] + a[1]*b[7];
	c[5] = a[5]*b[0] + a[0]*b[5] + a[3]*b[1] - a[1]*b[3] + a[4]*b[6] - a[6]*b[4] + a[7]*b[2] + a[2]*b[7];
	c[6] = a[6]*b[0] + a[0]*b[6] + a[1]*b[2] - a[2]*b[1] + a[5]*b[4] - a[4]*b[5] + a[7]*b[3] + a[3]*b[7];
	c[7] = a[0]*b[7] + a[7]*b[0] + a[1]*b[4] + a[4]*b[1] + a[2]*b[5] + a[5]*b[2] + a[3]*b[6] + a[6]*b[3];

	printf("Geometric product of\n");
	printf("[%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f]\n", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
	printf("[%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f]\n", b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
	printf("[%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f]\n", c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);

	// c0=a0b0+a1b1+a2b2+a3b3+a4b4+a5b5+a6b6+a7b7
	// c1=a0b1+a1b0-a2b6+a6b2+a3b5-a5b3+a7b4+a4b7
	// c2=a0b2+a2b0+a1b6-a6b1-a3b4+a4b3-a7b5-a5b7
	// c3=a0b3+a3b0-a1b5+a5b1+a2b4-a4b3+a7b4+a4b7
	// c4=a4b0+a0b4+a2b3-a3b2+a6b5-a5b6+a7b1+a1b7
	// c5=a5b0+a0b5+a3b1-a1b3+a4b6-a6b4+a7b2+a2b7
	// c6=a6b0+a0b6+a1b2-a2b1+a5b4-a4b5+a7b3+a3b7
	// c7=a0b7+a7b0+a1b4+a4b1+a2b5+a5b2+a3b6+a6b3

	return 0;
}
// int main(int argc, char **argv)
// {
// 	// Multiply two multivectors a and b to make c
// 	// Note: Bivectors have dimensions e_23 e_31 e_12
// 	// Vectors have dimensions e_1 e_2 e_3

// 	// scalar, vector3, multivector3, pseudoscalar = 8 values
// 	int a[8] = {1,2,3,4,5,6,7,8};
// 	int b[8] = {1,2,3,4,5,6,7,8};
// 	int c[8] = {0,0,0,0,0,0,0,0};

// 	// (a[0] + a[1:3] + a[4:6] + a[7]) ( b[0] + b[1:3] + b[4:6] + b[7]);

// 	// The scalar a[0] just scales everything
// 	// a[0] ( b[0] + b[1:3] + b[4:6] + b[7]);
// 	for (int i = 0; i < 8; i += 1){
// 		c[i] = a[0] * b[i];
// 	}

// 	// Multiplication by the vector a[1:3]
// 	// does some interesting things
// 	// a[1:3] ( b[0] + b[1:3] + b[4:6] + b[7]);

// 	// a[1:3] * b[0] = vector
// 	c[1] += a[1] * b[0];
// 	c[2] += a[2] * b[0];
// 	c[3] += a[3] * b[0];

// 	// a[1:3] * b[1:3] = scalar + bivector 23 31 12
// 	// scalar
// 	c[0] += a[1] * b[1];
// 	c[0] += a[2] * b[2];
// 	c[0] += a[3] * b[3];

// 	// bivector e23 e31 e12
// 	c[4] += a[2] * b[3] - a[3] * b[2];
// 	c[5] += a[3] * b[1] - a[1] * b[3];
// 	c[6] += a[1] * b[2] - a[2] * b[1];
	
// 	// a[1:3] * b[4:6] = pseudoscalar + vector
// 	// pseudoscalar
// 	c[7] += a[1] * b[4];
// 	c[7] += a[2] * b[5];
// 	c[7] += a[3] * b[6];

// 	// vector e1 e2 e3   e23 e31 e12
// 	c[1] += -a[2] * b[3+3] + a[3] * b[2+3]; // e1
// 	c[2] += -a[3] * b[1+3] + a[1] * b[3+3]; // e2
// 	c[3] += -a[1] * b[2+3] + a[2] * b[1+3]; // e3


// 	// a[1:3] * b[7] = bivector
// 	c[4] += a[1] * b[7]; // 23
// 	c[5] += a[2] * b[7]; // 31
// 	c[6] += a[3] * b[7]; // 12


// 	printf("[%d %d %d %d %d %d %d %d]\n", c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);

// 	// a[4:6] ( b[0] + b[1:3] + b[4:6] + b[7]);
// 	// Bivector * b multivector

// 	// bivector e23 e31 e12 * 1
// 	c[4] += a[4] * b[0];
// 	c[5] += a[5] * b[0];
// 	c[6] += a[6] * b[0];

// 	// a[4:6] * b[1:3] : e23 e31 e12 * e1 e2 e3
// 	// trivector
// 	c[7] += a[4] * b[1];
// 	c[7] += a[5] * b[2];
// 	c[7] += a[6] * b[3];
// 	// vector component
// 	c[1] += - a[2+3] * b[3] + a[3+3] * b[2]; // e1
// 	c[2] += - a[3+3] * b[1] + a[1+3] * b[3]; // e2
// 	c[3] += - a[1+3] * b[2] + a[2+3] * b[1]; // e3

// 	// a[4:6] * b[4:6] = e23 e31 e12  * e23 e31 e12 
// 	// scalar
// 	c[0] += a[4] * b[4];
// 	c[0] += a[5] * b[5];
// 	c[0] += a[6] * b[6];
// 	// bivector
// 	// 2*3 e3112 e1231  -e32 + e23 = element 1
// 	// 3*1 e1223 e2312 e13 e31 -> -e31 e31   2
// 	// 1*2 e2331 e3123 = -e12 el 3
// 	c[4] += - a[2+3] * b[3] + a[3+3] * b[2]; // e23
// 	c[5] += - a[3+3] * b[1] + a[1+3] * b[3]; // e31
// 	c[6] += - a[1+3] * b[2] + a[2+3] * b[1]; // e12

// 	// a[4:6] * b[7]
// 	// bivector * pseudoscalar = -vector
// 	c[1] = - a[4] * b[7];
// 	c[2] = - a[5] * b[7];
// 	c[3] = - a[6] * b[7];




// 	return 0;

// }
