#include "multivector.h"

int main(void)
{
    #define TAU 6.28318530718

    // #include "multiline_string_literal.h"
    // printf("%s", multiline_string_literal);

    arena_make(multivector_size);

    multivector_t v,a,b,r,spinor,spinor1,spinor2;

    v = multivector_vector(1,0,0);
    a = multivector_vector(1,0,0);
    b = multivector_vector(1/sqrt(2),1/sqrt(2),0);

    printf("\n");
    printf("multivector_length\n");
    printf("multiplying two vectors which have the same direction is equivalent to dotting them together\n");
    printf("which gives the multivector_length squared\n");
    printf("r = multivector_mul(2, multivector_vector(1,1,0), multivector_vector(1,1,0));\n");
    
    r = multivector_mul(2, multivector_vector(1,1,0), multivector_vector(1,1,0));
    multivector_print_scalar(r);

    printf("\n");
    printf("In spherical coordinates (r,theta,phi) where TAU = 2*Pi\n");
    printf("r = multivector_mul(2, multivector_vector_spherical(1, TAU/8, TAU/4), multivector_vector_spherical(1, TAU/8, TAU/4));\n");
    
    r = multivector_mul(2, multivector_vector_spherical(1, TAU/8, TAU/4), multivector_vector_spherical(1, TAU/8, TAU/4));
    multivector_print_scalar(r);
    
    printf("\n");
    printf("Area\n");
    printf("Multiplying two vectors which are orthogonal to each other will give the area of the rectangle\n");
    printf("r = multivector_mul(2, multivector_vector(1,0,0), multivector_vector(0,1,0));\n");
    
    r = multivector_mul(2, multivector_vector(1,0,0), multivector_vector(0,1,0));
    multivector_print_bivector(r);
    
    printf("\n");
    printf("Here we have two vectors in spherical coordinates.\n");
    printf("Multiplying them gives the dot product and the wedge product (similar to the cross product.\n");
    printf("r = multivector_mul(2, multivector_vector_spherical(1, TAU/8, TAU/8), multivector_vector_spherical(1, TAU/4, TAU/4));\n");
    
    r = multivector_mul(2, multivector_vector_spherical(1, TAU/8, TAU/8), multivector_vector_spherical(1, TAU/4, TAU/4));
    multivector_print(r);
    
    printf("\n");
    printf("volume\n");
    printf("Volume works great but you get a multivector_trivector\n");
    printf("r = multivector_mul(3, multivector_vector(1,0,0), multivector_vector(0,1,0), multivector_vector(0,0,1));\n");
    
    r = multivector_mul(3, multivector_vector(1,0,0), multivector_vector(0,1,0), multivector_vector(0,0,1));
    multivector_print_trivector(r);
    
    printf("\n");
    printf("r = multivector_mul(3, multivector_vector_spherical(1, TAU/8, TAU/4), multivector_vector_spherical(1, 3*TAU/8, TAU/4), multivector_vector(0,0,1));\n");
    
    r = multivector_mul(3, multivector_vector_spherical(1, TAU/8, TAU/4), multivector_vector_spherical(1, 3*TAU/8, TAU/4), multivector_vector(0,0,1));
    multivector_print_trivector(r);
    
    printf("A multivector_trivector is also known as a pseudoscalar since it's a single number\n");
    printf("but it squares to give a negative scalar\n");
    printf("\n");
    printf("\n");
    printf("2D rotation (complex numbers)\n");
    printf("A vector can be rotated by multiplying it by a bivector\n");
    printf("A bivector works like a complex number\n");
    printf("r = multivector_mul(2, multivector_vector(1,0,0), multivector_bivector(1,0,0)); \n");

    r = multivector_mul(2, multivector_vector(1,0,0), multivector_bivector(1,0,0)); 
    multivector_print_vector(r);
    
    printf("\n");
    printf("spinor = multivector_mul(2, multivector_vector(1,0,0), multivector_vector_spherical(1, TAU/12, TAU/4));\n");
    printf("r = multivector_mul(2, multivector_vector(1,0,0), spinor);\n");
    
    spinor = multivector_mul(2, multivector_vector(1,0,0), multivector_vector_spherical(1, TAU/12, TAU/4));
    r = multivector_mul(2, multivector_vector(1,0,0), spinor);
    multivector_print_vector(r);

    printf("\n");
    printf("\n");
    printf("3D rotation work in this way apparently\n");
    printf("To rotate a vector 'v' in the arc from vector 'a' to vector 'b'\n");
    printf("multiply(b,a,v,a,b);\n");
    printf("This will rotate v by twice the angle between a and b\n");
    printf("v = multivector_vector(1,0,0);\n");
    printf("a = multivector_vector_spherical(1, TAU/8, TAU/4);\n");
    printf("b = multivector_vector_spherical(1, TAU/8, TAU/8);\n");
    printf("r = multivector_mul(5, b,a,v,a,b);\n");

    v = multivector_vector(1,0,0);
    a = multivector_vector_spherical(1, TAU/8, TAU/4);
    b = multivector_vector_spherical(1, TAU/8, TAU/8);
    r = multivector_mul(5, b,a,v,a,b);

    multivector_print_vector(r);
    printf("\n");
    printf("Does it work just multiplying on one side? Not generally I think.\n");
    printf("spinor1 = multivector_mul(2, multivector_vector(1,0,0), multivector_vector_spherical(1,TAU/8,TAU/4))\n");
    printf("spinor2 = multivector_mul(2, multivector_vector(1,0,0), multivector_vector_spherical(1,TAU/8,TAU/4))\n");
    printf("multivector_mul(3, multivector_vector(1,0,0), spinor1, spinor2);\n");

    spinor1 = multivector_mul(2, multivector_vector(1,0,0), multivector_vector_spherical(1,TAU/8,TAU/4));
    spinor2 = multivector_mul(2, multivector_vector(1,0,0), multivector_vector_spherical(1,TAU/8,TAU/4));
    multivector_mul(3, multivector_vector(1,0,0), spinor1, spinor2);

    printf("\n");
    printf("chirality???\n");
    printf("r = multivector_mul(2, multivector_trivector(3), multivector_trivector(4));\n");
    r = multivector_mul(2, multivector_trivector(3), multivector_trivector(4));
    multivector_print(r);
    
    arena_free();

    return 0;

    #undef TAU

}
