/*
clang -std=c99 -Weverything mv_multivector.c; ./a.out

implements the multivector functions
init scalar vector bivector trivector vector_spherical 
geometric_product mul rotate rot 
print print_scalar print_vector print_bivector print_trivector 
arena_make arena_allocate arena_recycle arena_free arena arena_length arena_capacity 

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
// #include "short_type.h"

#define mv_length 8
typedef double* mv_t;

mv_t mv_init(void);
mv_t mv_scalar(double arg);
mv_t mv_vector(double a, double b, double c);
mv_t mv_bivector(double a, double b, double c);
mv_t mv_trivector(double arg);
mv_t mv_vector_spherical(double r, double theta, double phi);

mv_t mv_geometric_product(mv_t a, mv_t b);
mv_t mv_mul(int num, ...);

mv_t mv_rotate(mv_t v, mv_t a, mv_t b);
mv_t mv_rot(mv_t a, mv_t b);

void mv_print(mv_t a);
void mv_print_scalar(mv_t a);
void mv_print_vector(mv_t a);
void mv_print_bivector(mv_t a);
void mv_print_trivector(mv_t a);

void mv_arena_make(size_t cap);
mv_t mv_arena_allocate(void);
void mv_arena_recycle(void);
void mv_arena_free(void);

static mv_t mv_arena;
static size_t mv_arena_length;
static size_t mv_arena_capacity;


// === Arena Allocator =============

void mv_arena_make(size_t cap)
{
    mv_arena_length = 0;
    mv_arena_capacity = cap;
    mv_arena = malloc(mv_arena_capacity * sizeof(mv_t));
}

mv_t mv_arena_allocate(void)
{
    mv_t offset;
    offset = mv_arena + mv_arena_length;

    // realloc on overflow
    if (mv_arena_length + mv_length > mv_arena_capacity){
        mv_arena_capacity *= 2;
        mv_arena = realloc(mv_arena, mv_arena_capacity * sizeof(mv_t));
    }

    mv_arena_length += mv_length;
    return offset;
}

void mv_arena_recycle(void)
{
    mv_arena_length = 0;
}

void mv_arena_free(void)
{
    free(mv_arena);
}

// ===================================

mv_t mv_init(void)
{
    mv_t a = mv_arena_allocate();
    for (size_t i = 0; i < mv_length; i++) { a[i] = 0; }
    return a;
}


mv_t mv_scalar(double arg)
{
    mv_t a = mv_arena_allocate();
    for (size_t i = 0; i < mv_length; i++) { a[i] = 0; }
    a[0] = arg;
    return a;
}

mv_t mv_vector(double a, double b, double c)
{
    mv_t arr = mv_arena_allocate();
    for (size_t i = 0; i < mv_length; i++) { arr[i] = 0; }
    arr[1] = a;
    arr[2] = b;
    arr[3] = c;
    return arr;
}

mv_t mv_bivector(double a, double b, double c)
{
    mv_t arr = mv_arena_allocate();
    for (size_t i = 0; i < mv_length; i++) { arr[i] = 0; }
    arr[4] = a;
    arr[5] = b;
    arr[6] = c;
    return arr;
}

mv_t mv_trivector(double arg)
{
    mv_t a = mv_arena_allocate();
    for (size_t i = 0; i < mv_length; i++) { a[i] = 0; }
    a[7] = arg;
    return a;
}


mv_t mv_geometric_product(mv_t a, mv_t b)
{

    // multivector product in R3
    // c.e0     =   +a.e0*b.e0  +a.e1*b.e1  +a.e2*b.e2  +a.e3*b.e3  -a.e12*b.e12 -a.e23*b.e23 -a.e31*b.e31 -a.e123*b.e123;
    // c.e1     =   +a.e0*b.e1  +a.e1*b.e0  -a.e2*b.e12  +a.e3*b.e31  +a.e12*b.e2 -a.e23*b.e123 -a.e31*b.e3 -a.e123*b.e23;
    // c.e2     =   +a.e0*b.e2  +a.e1*b.e12  +a.e2*b.e0  -a.e3*b.e23  -a.e12*b.e1 +a.e23*b.e3 -a.e31*b.e123 -a.e123*b.e31;
    // c.e3     =   +a.e0*b.e3  -a.e1*b.e31  +a.e2*b.e23  +a.e3*b.e0  -a.e12*b.e123 -a.e23*b.e2 +a.e31*b.e1 -a.e123*b.e12;
    // c.e12    =   +a.e0*b.e12  +a.e1*b.e2  -a.e2*b.e1  +a.e3*b.e123  +a.e12*b.e0 -a.e23*b.e31 +a.e31*b.e23 +a.e123*b.e3;
    // c.e23    =   +a.e0*b.e23  +a.e1*b.e123  +a.e2*b.e3  -a.e3*b.e2  +a.e12*b.e31 +a.e23*b.e0 -a.e31*b.e12 +a.e123*b.e1;
    // c.e31    =   +a.e0*b.e31  -a.e1*b.e3  +a.e2*b.e123  +a.e3*b.e1  -a.e12*b.e23 +a.e23*b.e12 +a.e31*b.e0 +a.e123*b.e2;
    // c.e123   =   +a.e0*b.e123  +a.e1*b.e23  +a.e2*b.e31  +a.e3*b.e12  +a.e12*b.e3 +a.e23*b.e1 +a.e31*b.e2 +a.e123*b.e0;    

    // "All the pieces matter" - Lester Freamon

    mv_t c = mv_arena_allocate();
    for (size_t i = 0; i < mv_length; i++)
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

mv_t mv_mul(int num, ...)
{

   va_list valist;
   mv_t result = mv_scalar(1);
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      result = mv_geometric_product(result, va_arg(valist, mv_t));
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

   return result;
}

mv_t mv_rotate(mv_t v, mv_t a, mv_t b)
{
    // Rotate v by twice the angle between a and b;
    return mv_mul(5, b,a,v,a,b);
}

mv_t mv_rot(mv_t a, mv_t b)
{
    // rotate a by twice the angle between itself and b
    return mv_mul(5,b,a,a,a,b);
}

mv_t mv_vector_spherical(double r, double theta, double phi)
{
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    return mv_vector(
        r*cos(theta)*sin(phi), 
        r*sin(theta)*sin(phi), 
        r*cos(phi)
    );
}

void mv_print(mv_t a)
{

    printf("multivector( ");
    for (size_t i = 0; i < mv_length; i++)
    {
        printf("%.3f ", a[i]);
    }
    printf(")\n");
}

void mv_print_scalar(mv_t a)
{
    printf( "mv_scalar( %.3f )\n", a[0] );
}

void mv_print_vector(mv_t a)
{
    printf( "mv_vector( %.3f %.3f %.3f )\n", a[1],a[2],a[3]);
}

void mv_print_bivector(mv_t a)
{
    printf( "mv_bivector( %.3f %.3f %.3f )\n", a[4],a[5],a[6]);
}

void mv_print_trivector(mv_t a)
{
    printf( "mv_trivector( %.3f )\n", a[7]);
}

#undef mv_length


int mv_main(void)
{
    #define TAU 6.28318530718

    // #include "multiline_string_literal.h"
    // printf("%s", multiline_string_literal);

    mv_arena_make(1000);

    mv_t v = mv_vector(1,0,0);
    mv_t a = mv_vector(1,0,0);
    mv_t b = mv_vector(1/sqrt(2),1/sqrt(2),0);
    // mv_t c;
    mv_t r;
    mv_t spinor;
    mv_t spinor1;
    mv_t spinor2;

    printf("\n");
    printf("mv_length\n");
    printf("multiplying two vectors which have the same direction is equivalent to dotting them together\n");
    printf("which gives the mv_length squared\n");
    printf("r = mv_mul(2, mv_vector(1,1,0), mv_vector(1,1,0));\n");
    
    r = mv_mul(2, mv_vector(1,1,0), mv_vector(1,1,0));
    mv_print_scalar(r);

    printf("\n");
    printf("In spherical coordinates (r,theta,phi) where TAU = 2*Pi\n");
    printf("r = mv_mul(2, mv_vector_spherical(1, TAU/8, TAU/4), mv_vector_spherical(1, TAU/8, TAU/4));\n");
    
    r = mv_mul(2, mv_vector_spherical(1, TAU/8, TAU/4), mv_vector_spherical(1, TAU/8, TAU/4));
    mv_print_scalar(r);
    
    printf("\n");
    printf("Area\n");
    printf("Multiplying two vectors which are orthogonal to each other will give the area of the rectangle\n");
    printf("r = mv_mul(2, mv_vector(1,0,0), mv_vector(0,1,0));\n");
    
    r = mv_mul(2, mv_vector(1,0,0), mv_vector(0,1,0));
    mv_print_bivector(r);
    
    printf("\n");
    printf("Here we have two vectors in spherical coordinates.\n");
    printf("Multiplying them gives the dot product and the wedge product (similar to the cross product.\n");
    printf("r = mv_mul(2, mv_vector_spherical(1, TAU/8, TAU/8), mv_vector_spherical(1, TAU/4, TAU/4));\n");
    
    r = mv_mul(2, mv_vector_spherical(1, TAU/8, TAU/8), mv_vector_spherical(1, TAU/4, TAU/4));
    mv_print(r);
    
    printf("\n");
    printf("volume\n");
    printf("Volume works great but you get a mv_trivector\n");
    printf("r = mv_mul(3, mv_vector(1,0,0), mv_vector(0,1,0), mv_vector(0,0,1));\n");
    
    r = mv_mul(3, mv_vector(1,0,0), mv_vector(0,1,0), mv_vector(0,0,1));
    mv_print_trivector(r);
    
    printf("\n");
    printf("r = mv_mul(3, mv_vector_spherical(1, TAU/8, TAU/4), mv_vector_spherical(1, 3*TAU/8, TAU/4), mv_vector(0,0,1));\n");
    
    r = mv_mul(3, mv_vector_spherical(1, TAU/8, TAU/4), mv_vector_spherical(1, 3*TAU/8, TAU/4), mv_vector(0,0,1));
    mv_print_trivector(r);
    
    printf("A mv_trivector is also known as a pseudoscalar since it's a single number\n");
    printf("but it squares to give a negative scalar\n");
    printf("\n");
    printf("\n");
    printf("2D rotation (complex numbers)\n");
    printf("A vector can be rotated by multiplying it by a bivector\n");
    printf("A bivector works like a complex number\n");
    printf("r = mv_mul(2, mv_vector(1,0,0), mv_bivector(1,0,0)); \n");

    r = mv_mul(2, mv_vector(1,0,0), mv_bivector(1,0,0)); 
    mv_print_vector(r);
    
    printf("\n");
    printf("spinor = mv_mul(2, mv_vector(1,0,0), mv_vector_spherical(1, TAU/12, TAU/4));\n");
    printf("r = mv_mul(2, mv_vector(1,0,0), spinor);\n");
    
    spinor = mv_mul(2, mv_vector(1,0,0), mv_vector_spherical(1, TAU/12, TAU/4));
    r = mv_mul(2, mv_vector(1,0,0), spinor);
    mv_print_vector(r);

    printf("\n");
    printf("\n");
    printf("3D rotation work in this way apparently\n");
    printf("To rotate a vector 'v' in the arc from vector 'a' to vector 'b'\n");
    printf("multiply(b,a,v,a,b);\n");
    printf("This will rotate v by twice the angle between a and b\n");
    printf("v = mv_vector(1,0,0);\n");
    printf("a = mv_vector_spherical(1, TAU/8, TAU/4);\n");
    printf("b = mv_vector_spherical(1, TAU/8, TAU/8);\n");
    printf("r = mv_mul(5, b,a,v,a,b);\n");

    v = mv_vector(1,0,0);
    a = mv_vector_spherical(1, TAU/8, TAU/4);
    b = mv_vector_spherical(1, TAU/8, TAU/8);
    r = mv_mul(5, b,a,v,a,b);

    mv_print_vector(r);
    printf("\n");
    printf("Does it work just multiplying on one side? Not generally I think.\n");
    printf("spinor1 = mv_mul(2, mv_vector(1,0,0), mv_vector_spherical(1,TAU/8,TAU/4))\n");
    printf("spinor2 = mv_mul(2, mv_vector(1,0,0), mv_vector_spherical(1,TAU/8,TAU/4))\n");
    printf("mv_mul(3, mv_vector(1,0,0), spinor1, spinor2);\n");

    spinor1 = mv_mul(2, mv_vector(1,0,0), mv_vector_spherical(1,TAU/8,TAU/4));
    spinor2 = mv_mul(2, mv_vector(1,0,0), mv_vector_spherical(1,TAU/8,TAU/4));
    mv_mul(3, mv_vector(1,0,0), spinor1, spinor2);

    printf("\n");
    printf("chirality???\n");
    printf("r = mv_mul(2, mv_trivector(3), mv_trivector(4));\n");
    r = mv_mul(2, mv_trivector(3), mv_trivector(4));
    mv_print(r);
    
    mv_arena_free();

    return 0;

    #undef TAU

}
