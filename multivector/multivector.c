#include "multivector.h"

// === Arena Allocator =============

void multivector_arena_make(size_t cap)
{
    multivector_arena_length = 0;
    multivector_arena_capacity = cap;
    multivector_arena = malloc(multivector_arena_capacity * sizeof(multivector_t));
}

multivector_t multivector_arena_allocate(void)
{
    multivector_t offset;
    offset = multivector_arena + multivector_arena_length;

    // realloc on overflow
    if (multivector_arena_length + multivector_length > multivector_arena_capacity){
        multivector_arena_capacity *= 2;
        multivector_arena = realloc(multivector_arena, multivector_arena_capacity * sizeof(multivector_t));
    }

    multivector_arena_length += multivector_length;
    return offset;
}

void multivector_arena_recycle(void)
{
    multivector_arena_length = 0;
}

void multivector_arena_free(void)
{
    free(multivector_arena);
}

// ===================================

multivector_t multivector_init(void)
{
    multivector_t a = multivector_arena_allocate();
    for (size_t i = 0; i < multivector_length; i++) { a[i] = 0; }
    return a;
}


multivector_t multivector_scalar(double arg)
{
    multivector_t a = multivector_arena_allocate();
    for (size_t i = 0; i < multivector_length; i++) { a[i] = 0; }
    a[0] = arg;
    return a;
}

multivector_t multivector_vector(double a, double b, double c)
{
    multivector_t arr = multivector_arena_allocate();
    for (size_t i = 0; i < multivector_length; i++) { arr[i] = 0; }
    arr[1] = a;
    arr[2] = b;
    arr[3] = c;
    return arr;
}

multivector_t multivector_bivector(double a, double b, double c)
{
    multivector_t arr = multivector_arena_allocate();
    for (size_t i = 0; i < multivector_length; i++) { arr[i] = 0; }
    arr[4] = a;
    arr[5] = b;
    arr[6] = c;
    return arr;
}

multivector_t multivector_trivector(double arg)
{
    multivector_t a = multivector_arena_allocate();
    for (size_t i = 0; i < multivector_length; i++) { a[i] = 0; }
    a[7] = arg;
    return a;
}


multivector_t multivector_geometric_product(multivector_t a, multivector_t b)
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

    multivector_t c = multivector_arena_allocate();
    for (size_t i = 0; i < multivector_length; i++)
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

multivector_t multivector_mul(int num, ...)
{

   va_list valist;
   multivector_t result = multivector_scalar(1);
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      result = multivector_geometric_product(result, va_arg(valist, multivector_t));
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

   return result;
}

multivector_t multivector_rotate(multivector_t v, multivector_t a, multivector_t b)
{
    // Rotate v by twice the angle between a and b;
    return multivector_mul(5, b,a,v,a,b);
}

multivector_t multivector_rot(multivector_t a, multivector_t b)
{
    // rotate a by twice the angle between itself and b
    return multivector_mul(5,b,a,a,a,b);
}

multivector_t multivector_vector_spherical(double r, double theta, double phi)
{
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    return multivector_vector(
        r*cos(theta)*sin(phi), 
        r*sin(theta)*sin(phi), 
        r*cos(phi)
    );
}

void multivector_print(multivector_t a)
{

    printf("multivector( ");
    for (size_t i = 0; i < multivector_length; i++)
    {
        printf("%.3f ", a[i]);
    }
    printf(")\n");
}

void multivector_print_scalar(multivector_t a)
{
    printf( "multivector_scalar( %.3f )\n", a[0] );
}

void multivector_print_vector(multivector_t a)
{
    printf( "multivector_vector( %.3f %.3f %.3f )\n", a[1],a[2],a[3]);
}

void multivector_print_bivector(multivector_t a)
{
    printf( "multivector_bivector( %.3f %.3f %.3f )\n", a[4],a[5],a[6]);
}

void multivector_print_trivector(multivector_t a)
{
    printf( "multivector_trivector( %.3f )\n", a[7]);
}
