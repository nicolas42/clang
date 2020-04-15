#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

/*
clang -std=c99 -Weverything multivector.c; ./a.out

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
#include "short_type.h"

namespace multivector {

#define length 8
typedef f64* T;

T init(void);
T scalar(f64 arg);
T vector(f64 a, f64 b, f64 c);
T bivector(f64 a, f64 b, f64 c);
T trivector(f64 arg);
T vector_spherical(f64 r, f64 theta, f64 phi);

T geometric_product(T a, T b);
T mul(int num, ...);

T rotate(T v, T a, T b);
T rot(T a, T b);

void print(T a);
void print_scalar(T a);
void print_vector(T a);
void print_bivector(T a);
void print_trivector(T a);

void arena_make(size_t cap);
T arena_allocate(void);
void arena_recycle(void);
void arena_free(void);

static T arena;
static size_t arena_length;
static size_t arena_capacity;


// === Arena Allocator =============

void arena_make(size_t cap)
{
    arena_length = 0;
    arena_capacity = cap;
    arena = T(malloc(arena_capacity * sizeof(T)));
}

T arena_allocate(void)
{
    T offset;
    offset = arena + arena_length;

    // realloc on overflow
    if (arena_length + length > arena_capacity){
        arena_capacity *= 2;
        arena = T(realloc(arena, arena_capacity * sizeof(T)));
    }

    arena_length += length;
    return offset;
}

void arena_recycle(void)
{
    arena_length = 0;
}

void arena_free(void)
{
    free(arena);
}

// ===================================

T init(void)
{
    T a = arena_allocate();
    for (size_t i = 0; i < length; i++) { a[i] = 0; }
    return a;
}


T scalar(f64 arg)
{
    T a = arena_allocate();
    for (size_t i = 0; i < length; i++) { a[i] = 0; }
    a[0] = arg;
    return a;
}

T vector(f64 a, f64 b, f64 c)
{
    T arr = arena_allocate();
    for (size_t i = 0; i < length; i++) { arr[i] = 0; }
    arr[1] = a;
    arr[2] = b;
    arr[3] = c;
    return arr;
}

T bivector(f64 a, f64 b, f64 c)
{
    T arr = arena_allocate();
    for (size_t i = 0; i < length; i++) { arr[i] = 0; }
    arr[4] = a;
    arr[5] = b;
    arr[6] = c;
    return arr;
}

T trivector(f64 arg)
{
    T a = arena_allocate();
    for (size_t i = 0; i < length; i++) { a[i] = 0; }
    a[7] = arg;
    return a;
}


T geometric_product(T a, T b)
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

    T c = arena_allocate();
    for (size_t i = 0; i < length; i++)
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

T mul(int num, ...)
{

   va_list valist;
   T result = scalar(1);
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      result = geometric_product(result, va_arg(valist, T));
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

   return result;
}

T rotate(T v, T a, T b)
{
    // Rotate v by twice the angle between a and b;
    return mul(5, b,a,v,a,b);
}

T rot(T a, T b)
{
    // rotate a by twice the angle between itself and b
    return mul(5,b,a,a,a,b);
}

T vector_spherical(f64 r, f64 theta, f64 phi)
{
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    return vector(
        r*cos(theta)*sin(phi), 
        r*sin(theta)*sin(phi), 
        r*cos(phi)
    );
}

void print(T a)
{

    printf("multivector( ");
    for (size_t i = 0; i < length; i++)
    {
        printf("%.3f ", a[i]);
    }
    printf(")\n");
}

void print_scalar(T a)
{
    printf( "scalar( %.3f )\n", a[0] );
}

void print_vector(T a)
{
    printf( "vector( %.3f %.3f %.3f )\n", a[1],a[2],a[3]);
}

void print_bivector(T a)
{
    printf( "bivector( %.3f %.3f %.3f )\n", a[4],a[5],a[6]);
}

void print_trivector(T a)
{
    printf( "trivector( %.3f )\n", a[7]);
}

#undef length


int main(void)
{
    #define TAU 6.28318530718

    // #include "multiline_string_literal.h"
    // printf("%s", multiline_string_literal);

    arena_make(1000);

    T v = vector(1,0,0);
    T a = vector(1,0,0);
    T b = vector(1/sqrt(2),1/sqrt(2),0);
    // T c;
    T r;
    T spinor;
    T spinor1;
    T spinor2;

    printf("\n");
    printf("length\n");
    printf("multiplying two vectors which have the same direction is equivalent to dotting them together\n");
    printf("which gives the length squared\n");
    printf("r = mul(2, vector(1,1,0), vector(1,1,0));\n");
    
    r = mul(2, vector(1,1,0), vector(1,1,0));
    print_scalar(r);

    printf("\n");
    printf("In spherical coordinates (r,theta,phi) where TAU = 2*Pi\n");
    printf("r = mul(2, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, TAU/8, TAU/4));\n");
    
    r = mul(2, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, TAU/8, TAU/4));
    print_scalar(r);
    
    printf("\n");
    printf("Area\n");
    printf("Multiplying two vectors which are orthogonal to each other will give the area of the rectangle\n");
    printf("r = mul(2, vector(1,0,0), vector(0,1,0));\n");
    
    r = mul(2, vector(1,0,0), vector(0,1,0));
    print_bivector(r);
    
    printf("\n");
    printf("Here we have two vectors in spherical coordinates.\n");
    printf("Multiplying them gives the dot product and the wedge product (similar to the cross product.\n");
    printf("r = mul(2, vector_spherical(1, TAU/8, TAU/8), vector_spherical(1, TAU/4, TAU/4));\n");
    
    r = mul(2, vector_spherical(1, TAU/8, TAU/8), vector_spherical(1, TAU/4, TAU/4));
    print(r);
    
    printf("\n");
    printf("volume\n");
    printf("Volume works great but you get a trivector\n");
    printf("r = mul(3, vector(1,0,0), vector(0,1,0), vector(0,0,1));\n");
    
    r = mul(3, vector(1,0,0), vector(0,1,0), vector(0,0,1));
    print_trivector(r);
    
    printf("\n");
    printf("r = mul(3, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, 3*TAU/8, TAU/4), vector(0,0,1));\n");
    
    r = mul(3, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, 3*TAU/8, TAU/4), vector(0,0,1));
    print_trivector(r);
    
    printf("A trivector is also known as a pseudoscalar since it's a single number\n");
    printf("but it squares to give a negative scalar\n");
    printf("\n");
    printf("\n");
    printf("2D rotation (complex numbers)\n");
    printf("A vector can be rotated by multiplying it by a bivector\n");
    printf("A bivector works like a complex number\n");
    printf("r = mul(2, vector(1,0,0), bivector(1,0,0)); \n");

    r = mul(2, vector(1,0,0), bivector(1,0,0)); 
    print_vector(r);
    
    printf("\n");
    printf("spinor = mul(2, vector(1,0,0), vector_spherical(1, TAU/12, TAU/4));\n");
    printf("r = mul(2, vector(1,0,0), spinor);\n");
    
    spinor = mul(2, vector(1,0,0), vector_spherical(1, TAU/12, TAU/4));
    r = mul(2, vector(1,0,0), spinor);
    print_vector(r);

    printf("\n");
    printf("\n");
    printf("3D rotation work in this way apparently\n");
    printf("To rotate a vector 'v' in the arc from vector 'a' to vector 'b'\n");
    printf("multiply(b,a,v,a,b);\n");
    printf("This will rotate v by twice the angle between a and b\n");
    printf("v = vector(1,0,0);\n");
    printf("a = vector_spherical(1, TAU/8, TAU/4);\n");
    printf("b = vector_spherical(1, TAU/8, TAU/8);\n");
    printf("r = mul(5, b,a,v,a,b);\n");

    v = vector(1,0,0);
    a = vector_spherical(1, TAU/8, TAU/4);
    b = vector_spherical(1, TAU/8, TAU/8);
    r = mul(5, b,a,v,a,b);

    print_vector(r);
    printf("\n");
    printf("Does it work just multiplying on one side? Not generally I think.\n");
    printf("spinor1 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4))\n");
    printf("spinor2 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4))\n");
    printf("mul(3, vector(1,0,0), spinor1, spinor2);\n");

    spinor1 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4));
    spinor2 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4));
    mul(3, vector(1,0,0), spinor1, spinor2);

    printf("\n");
    printf("chirality???\n");
    printf("r = mul(2, trivector(3), trivector(4));\n");
    r = mul(2, trivector(3), trivector(4));
    print(r);
    
    arena_free();

    return 0;

    #undef TAU

}

}

#endif
