/*
clang -std=c99 -Weverything multivector.c; ./a.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
// #include "short_type.h"

#define m_length 8
typedef double* m_t;

m_t m_init(void);
m_t m_scalar(double arg);
m_t m_vector(double a, double b, double c);
m_t m_bivector(double a, double b, double c);
m_t m_trivector(double arg);
m_t m_vector_spherical(double r, double theta, double phi);

m_t m_geometric_product(m_t a, m_t b);
m_t m_mul(int num, ...);

m_t m_rotate(m_t v, m_t a, m_t b);
m_t m_rot(m_t a, m_t b);

void m_print(m_t a);
void m_print_scalar(m_t a);
void m_print_vector(m_t a);
void m_print_bivector(m_t a);
void m_print_trivector(m_t a);

void m_arena_make(size_t cap);
m_t m_arena_allocate(void);
void m_arena_recycle(void);
void m_arena_free(void);

static m_t m_arena;
static size_t m_arena_length;
static size_t m_arena_capacity;


// === Arena Allocator =============

void m_arena_make(size_t cap)
{
    m_arena_length = 0;
    m_arena_capacity = cap;
    m_arena = malloc(m_arena_capacity * sizeof(m_t));
}

m_t m_arena_allocate(void)
{
    m_t offset;
    offset = m_arena + m_arena_length;

    // realloc on overflow
    if (m_arena_length + m_length > m_arena_capacity){
        m_arena_capacity *= 2;
        m_arena = realloc(m_arena, m_arena_capacity * sizeof(m_t));
    }

    m_arena_length += m_length;
    return offset;
}

void m_arena_recycle(void)
{
    m_arena_length = 0;
}

void m_arena_free(void)
{
    free(m_arena);
}

// ===================================

m_t m_init(void)
{
    m_t a = m_arena_allocate();
    for (size_t i = 0; i < m_length; i++) { a[i] = 0; }
    return a;
}


m_t m_scalar(double arg)
{
    m_t a = m_arena_allocate();
    for (size_t i = 0; i < m_length; i++) { a[i] = 0; }
    a[0] = arg;
    return a;
}

m_t m_vector(double a, double b, double c)
{
    m_t arr = m_arena_allocate();
    for (size_t i = 0; i < m_length; i++) { arr[i] = 0; }
    arr[1] = a;
    arr[2] = b;
    arr[3] = c;
    return arr;
}

m_t m_bivector(double a, double b, double c)
{
    m_t arr = m_arena_allocate();
    for (size_t i = 0; i < m_length; i++) { arr[i] = 0; }
    arr[4] = a;
    arr[5] = b;
    arr[6] = c;
    return arr;
}

m_t m_trivector(double arg)
{
    m_t a = m_arena_allocate();
    for (size_t i = 0; i < m_length; i++) { a[i] = 0; }
    a[7] = arg;
    return a;
}


m_t m_geometric_product(m_t a, m_t b)
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

    m_t c = m_arena_allocate();
    for (size_t i = 0; i < m_length; i++)
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

m_t m_mul(int num, ...)
{

   va_list valist;
   m_t result = m_scalar(1);
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      result = m_geometric_product(result, va_arg(valist, m_t));
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

   return result;
}

m_t m_rotate(m_t v, m_t a, m_t b)
{
    // Rotate v by twice the angle between a and b;
    return m_mul(5, b,a,v,a,b);
}

m_t m_rot(m_t a, m_t b)
{
    // rotate a by twice the angle between itself and b
    return m_mul(5,b,a,a,a,b);
}

m_t m_vector_spherical(double r, double theta, double phi)
{
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    return m_vector(
        r*cos(theta)*sin(phi), 
        r*sin(theta)*sin(phi), 
        r*cos(phi)
    );
}

void m_print(m_t a)
{

    printf("multivector( ");
    for (size_t i = 0; i < m_length; i++)
    {
        printf("%.3f ", a[i]);
    }
    printf(")\n");
}

void m_print_scalar(m_t a)
{
    printf( "m_scalar( %.3f )\n", a[0] );
}

void m_print_vector(m_t a)
{
    printf( "m_vector( %.3f %.3f %.3f )\n", a[1],a[2],a[3]);
}

void m_print_bivector(m_t a)
{
    printf( "m_bivector( %.3f %.3f %.3f )\n", a[4],a[5],a[6]);
}

void m_print_trivector(m_t a)
{
    printf( "m_trivector( %.3f )\n", a[7]);
}

#undef m_length


int main(void)
{
    #define TAU 6.28318530718

    // #include "multiline_string_literal.h"
    // printf("%s", multiline_string_literal);

    m_arena_make(1000);

    m_t v = m_vector(1,0,0);
    m_t a = m_vector(1,0,0);
    m_t b = m_vector(1/sqrt(2),1/sqrt(2),0);
    // m_t c;
    m_t r;
    m_t spinor;
    m_t spinor1;
    m_t spinor2;

    printf("\n");
    printf("m_length\n");
    printf("multiplying two vectors which have the same direction is equivalent to dotting them together\n");
    printf("which gives the m_length squared\n");
    printf("r = m_mul(2, m_vector(1,1,0), m_vector(1,1,0));\n");
    
    r = m_mul(2, m_vector(1,1,0), m_vector(1,1,0));
    m_print_scalar(r);

    printf("\n");
    printf("In spherical coordinates (r,theta,phi) where TAU = 2*Pi\n");
    printf("r = m_mul(2, m_vector_spherical(1, TAU/8, TAU/4), m_vector_spherical(1, TAU/8, TAU/4));\n");
    
    r = m_mul(2, m_vector_spherical(1, TAU/8, TAU/4), m_vector_spherical(1, TAU/8, TAU/4));
    m_print_scalar(r);
    
    printf("\n");
    printf("Area\n");
    printf("Multiplying two vectors which are orthogonal to each other will give the area of the rectangle\n");
    printf("r = m_mul(2, m_vector(1,0,0), m_vector(0,1,0));\n");
    
    r = m_mul(2, m_vector(1,0,0), m_vector(0,1,0));
    m_print_bivector(r);
    
    printf("\n");
    printf("Here we have two vectors in spherical coordinates.\n");
    printf("Multiplying them gives the dot product and the wedge product (similar to the cross product.\n");
    printf("r = m_mul(2, m_vector_spherical(1, TAU/8, TAU/8), m_vector_spherical(1, TAU/4, TAU/4));\n");
    
    r = m_mul(2, m_vector_spherical(1, TAU/8, TAU/8), m_vector_spherical(1, TAU/4, TAU/4));
    m_print(r);
    
    printf("\n");
    printf("volume\n");
    printf("Volume works great but you get a m_trivector\n");
    printf("r = m_mul(3, m_vector(1,0,0), m_vector(0,1,0), m_vector(0,0,1));\n");
    
    r = m_mul(3, m_vector(1,0,0), m_vector(0,1,0), m_vector(0,0,1));
    m_print_trivector(r);
    
    printf("\n");
    printf("r = m_mul(3, m_vector_spherical(1, TAU/8, TAU/4), m_vector_spherical(1, 3*TAU/8, TAU/4), m_vector(0,0,1));\n");
    
    r = m_mul(3, m_vector_spherical(1, TAU/8, TAU/4), m_vector_spherical(1, 3*TAU/8, TAU/4), m_vector(0,0,1));
    m_print_trivector(r);
    
    printf("A m_trivector is also known as a pseudoscalar since it's a single number\n");
    printf("but it squares to give a negative scalar\n");
    printf("\n");
    printf("\n");
    printf("2D rotation (complex numbers)\n");
    printf("A vector can be rotated by multiplying it by a bivector\n");
    printf("A bivector works like a complex number\n");
    printf("r = m_mul(2, m_vector(1,0,0), m_bivector(1,0,0)); \n");

    r = m_mul(2, m_vector(1,0,0), m_bivector(1,0,0)); 
    m_print_vector(r);
    
    printf("\n");
    printf("spinor = m_mul(2, m_vector(1,0,0), m_vector_spherical(1, TAU/12, TAU/4));\n");
    printf("r = m_mul(2, m_vector(1,0,0), spinor);\n");
    
    spinor = m_mul(2, m_vector(1,0,0), m_vector_spherical(1, TAU/12, TAU/4));
    r = m_mul(2, m_vector(1,0,0), spinor);
    m_print_vector(r);

    printf("\n");
    printf("\n");
    printf("3D rotation work in this way apparently\n");
    printf("To rotate a vector 'v' in the arc from vector 'a' to vector 'b'\n");
    printf("multiply(b,a,v,a,b);\n");
    printf("This will rotate v by twice the angle between a and b\n");
    printf("v = m_vector(1,0,0);\n");
    printf("a = m_vector_spherical(1, TAU/8, TAU/4);\n");
    printf("b = m_vector_spherical(1, TAU/8, TAU/8);\n");
    printf("r = m_mul(5, b,a,v,a,b);\n");

    v = m_vector(1,0,0);
    a = m_vector_spherical(1, TAU/8, TAU/4);
    b = m_vector_spherical(1, TAU/8, TAU/8);
    r = m_mul(5, b,a,v,a,b);

    m_print_vector(r);
    printf("\n");
    printf("Does it work just multiplying on one side? Not generally I think.\n");
    printf("spinor1 = m_mul(2, m_vector(1,0,0), m_vector_spherical(1,TAU/8,TAU/4))\n");
    printf("spinor2 = m_mul(2, m_vector(1,0,0), m_vector_spherical(1,TAU/8,TAU/4))\n");
    printf("m_mul(3, m_vector(1,0,0), spinor1, spinor2);\n");

    spinor1 = m_mul(2, m_vector(1,0,0), m_vector_spherical(1,TAU/8,TAU/4));
    spinor2 = m_mul(2, m_vector(1,0,0), m_vector_spherical(1,TAU/8,TAU/4));
    m_mul(3, m_vector(1,0,0), spinor1, spinor2);

    printf("\n");
    printf("chirality???\n");
    printf("r = m_mul(2, m_trivector(3), m_trivector(4));\n");
    r = m_mul(2, m_trivector(3), m_trivector(4));
    m_print(r);
    
    m_arena_free();

    return 0;

    #undef TAU

}
