#include "mv_multivector.h"

int main(void)
{
    #define TAU 6.28318530718

    // #include "multiline_string_literal.h"
    // printf("%s", multiline_string_literal);

    mv_arena_make(1000);

    mv_t v,a,b,r,spinor,spinor1,spinor2;

    v = mv_vector(1,0,0);
    a = mv_vector(1,0,0);
    b = mv_vector(1/sqrt(2),1/sqrt(2),0);

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
