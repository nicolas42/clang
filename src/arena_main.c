#include "arena_allocator.h"
#include "multivector.h"

int main(void)
{
    arena_make(1*multivector_size);

    multivector_t a;
    a = multivector_vector(1,2,3);

    for (size_t i = 0; i < multivector_length; i++) {
        printf("%.2f ", a[i]);
    }
    printf("\n");
    
    return 0;
}
