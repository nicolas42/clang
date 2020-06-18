/*
clang -lm cpp_multivector.hpp cpp_multivector_main.cpp 
*/
#include "cpp_multivector.hpp"

int main(void)
{
    using namespace multivector;

    #define TAU 6.28318530718

    // #include "multiline_string_literal.h"
    // printf("%s", multiline_string_literal);

    multivector::arena_make(1000);

    multivector::T v,a,b,r,spinor,spinor1,spinor2;

    v = vector(1,0,0);
    a = vector(1,0,0);
    b = vector(1/sqrt(2),1/sqrt(2),0);

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
