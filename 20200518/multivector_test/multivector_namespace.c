#include "multivector_namespace.h"


int main(void)
{
    // #include "multiline_string_literal.h"
    // printf("%s", multiline_string_literal);

    arena_length = 0;
    arena_capacity = 10000;
    arena = malloc(arena_capacity * sizeof(multivector_t));

    #define T 6.28318530718


    multivector_t v = vector(1,0,0);
    multivector_t a = vector(1,0,0);
    multivector_t b = vector(1/sqrt(2),1/sqrt(2),0);
    // multivector_t c;
    multivector_t r;
    multivector_t spinor;
    
    printf("\n");
    printf("length\n");
    printf("multiplying two vectors which have the same direction is equivalent to dotting them together\n");
    printf("which gives the length squared\n");
    printf("r = mul(2, vector(1,1,0), vector(1,1,0));\n");
    
    r = mul(2, vector(1,1,0), vector(1,1,0));
    print_scalar(r);

    free(arena);

    return 0;

#undef T

}

