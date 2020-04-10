#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

// Why this warning?
// a.c:11:12: warning: incompatible pointer types assigning to 'double *' from 'double **'; dereference with * [-Wincompatible-pointer-types]
//     offset = temporary_storage + temporary_storage_length;
//            ^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              *(                                          )
// 1 warning generated.

double *temporary_storage[1000000];
int temporary_storage_length = 0;

double* arena_allocate(int len){
    double* offset;
    offset = temporary_storage + temporary_storage_length;
    temporary_storage_length += len;
    return offset;
}


double* init(){
    double* a = arena_allocate(8);
    for (size_t i = 0; i < 8; i++) { a[i] = 0; }
    return a;
}


double* scalar(double arg){
    double* a = arena_allocate(8);
    for (size_t i = 0; i < 8; i++) { a[i] = 0; }
    a[0] = arg;
    return a;
}

double* vector(double a, double b, double c){
    double* arr = arena_allocate(8);
    for (size_t i = 0; i < 8; i++) { arr[i] = 0; }
    arr[1] = a;
    arr[2] = b;
    arr[3] = c;
    return arr;
}

double* bivector(double a, double b, double c){
    double* arr = arena_allocate(8);
    for (size_t i = 0; i < 8; i++) { arr[i] = 0; }
    arr[4] = a;
    arr[5] = b;
    arr[6] = c;
    return arr;
}

double* trivector(double arg){
    double* a = arena_allocate(8);
    for (size_t i = 0; i < 8; i++) { a[i] = 0; }
    a[7] = arg;
    return a;
}


double* geometric_product(double* a, double* b){

    double* c = arena_allocate(8);
    for (size_t i = 0; i < 8; i++)
    {
        c[i] = 0;
    }
    c[0]   =   +a[0]*b[0]  +a[1]*b[1]  +a[2]*b[2]  +a[3]*b[3]  -a[4]*b[4] -a[5]*b[5] -a[6]*b[6] -a[7]*b[7];
    c[1]   =   +a[0]*b[1]  +a[1]*b[0]  -a[2]*b[4]  +a[3]*b[6]  +a[4]*b[2] -a[5]*b[7] -a[6]*b[3] -a[7]*b[5];
    c[2]   =   +a[0]*b[2]  +a[1]*b[4]  +a[2]*b[0]  -a[3]*b[5]  -a[4]*b[1] +a[5]*b[3] -a[6]*b[7] -a[7]*b[6];
    c[3]   =   +a[0]*b[3]  -a[1]*b[6]  +a[2]*b[5]  +a[3]*b[0]  -a[4]*b[7] -a[5]*b[2] +a[6]*b[1] -a[7]*b[4];
    c[4]   =   +a[0]*b[4]  +a[1]*b[2]  -a[2]*b[1]  +a[3]*b[7]  +a[4]*b[0] -a[5]*b[6] +a[6]*b[5] +a[7]*b[3];
    c[5]   =   +a[0]*b[5]  +a[1]*b[7]  +a[2]*b[3]  -a[3]*b[2]  +a[4]*b[6] +a[5]*b[0] -a[6]*b[4] +a[7]*b[1];
    c[6]   =   +a[0]*b[6]  -a[1]*b[3]  +a[2]*b[7]  +a[3]*b[1]  -a[4]*b[5] +a[5]*b[4] +a[6]*b[0] +a[7]*b[2];
    c[7]   =   +a[0]*b[7]  +a[1]*b[5]  +a[2]*b[6]  +a[3]*b[4]  +a[4]*b[3] +a[5]*b[1] +a[6]*b[2] +a[7]*b[0];    
    return c;
}

double* mul(int num,...) {

   va_list valist;
   double* result = scalar(1);
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      result = geometric_product(result, va_arg(valist, double*));
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

   return result;
}

double* rotate(double* v,double* a,double* b){
    // Rotate v by twice the angle between a and b;
    return mul(5, b,a,v,a,b);
}

double* rot(double* a,double* b){
    // rotate a by twice the angle between itself and b
    return mul(5,b,a,a,a,b);
}

double* vector_spherical(double r, double theta, double phi){
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    return vector(
        r*cos(theta)*sin(phi), 
        r*sin(theta)*sin(phi), 
        r*cos(phi)
    );
}

void print(double* a){

    printf("multivector( ");
    for (size_t i = 0; i < 8; i++)
    {
        printf("%.3f ", a[i]);
    }
    printf(")\n");
}

void print_scalar(double* a){
    printf( "scalar( %.3f )\n", a[0] );
}

void print_vector(double* a){
    printf( "vector( %.3f %.3f %.3f )\n", a[1],a[2],a[3]);
}

void print_bivector(double* a){
    printf( "bivector( %.3f %.3f %.3f )\n", a[4],a[5],a[6]);
}

void print_trivector(double* a){
    printf( "trivector( %.3f )\n", a[7]);
}

#define PI 3.14159265359
#define T 6.28318530718




// int main(int argc, char **argv)
// {
// 	double v[8] = {0, 1,0,0, 0,0,0, 0}; 
// 	double a[8] = {0, 1,0,0, 0,0,0, 0}; 
// 	double b[8] = {0, 1/sqrt(2), 1/sqrt(2),0, 0,0,0, 0};
// 	double *c;
// 	int i;


// 	// c = mul(b, mul(a, mul(v, mul(a, b))));
//     c = multiply(5, b,a,v,a,b);

// 	printf("[%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f]\n", 
// 			c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);

// 	// for (i = 0; i < garbage_length; i += 1){
// 	// 	free(garbage[i]);
// 	// }
// 	return 0;
// }



int main(int argc, char** argv){
 
    double* v = vector(1,0,0);
    double* a = vector(1,0,0);
    double* b = vector(1/sqrt(2),1/sqrt(2),0);
    double* c;
    double* r;
    double* spinor;
    
    // length
    a = vector(1,1,0);
    r = mul(2,a,a);
    print_scalar(r);

    r = mul(2, vector_spherical(1, T/8, T/4),vector_spherical(1, T/8, T/4));
    print_scalar(r);

    // area
    r = mul(2, vector(1,0,0), vector(0,1,0));
    print_bivector(r);

    r = mul(2, vector_spherical(1,T/8, T/4), vector_spherical(1,3*T/8, T/4));
    print_bivector(r);

    // volume
    r = mul(3, vector(1,0,0), vector(0,1,0), vector(0,0,1));
    print_trivector(r);

    r = mul(3, vector_spherical(1, T/8, T/4), vector_spherical(1, 3*T/8, T/4), vector(0,0,1));
    print_trivector(r);

    // 2D rotation (complex numbers)
    r = mul(2, vector(1,0,0), bivector(1,0,0)); 
    print(r);

    spinor = mul(2, vector(1,0,0), vector_spherical(1, T/12, T/4));
    r = mul(2, vector(1,0,0), spinor);
    print(r);


    // 3D rotation (multiply v by twice the angle between a and b)
    v = vector(1,0,0);
    a = vector_spherical(1, T/8, T/4);
    b = vector_spherical(1, T/8, T/8);
    r = mul(5, b,a,v,a,b);
    print(r);

    // spinor1 = mul(vector(1,0,0), vector_spherical(1,T/8))
    // spinor2 = mul(vector(1,0,0), vector_spherical(1,T/8,T/4))
    // mul(vector(1,0,0), spinor1, spinor2);

    // chirality???
    mul(2, trivector(3), trivector(4));

    return 0;
}