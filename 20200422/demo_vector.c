/*
demo_vector
clang -Weverything -Wno-cast-align vector.h demo_vector.c ; ./a.out
*/
#include "vector.h"

typedef struct test_struct {
    int x; int y;
} test_struct;

#define T test_struct
#define vector(a) ((T*)a.data)
#define vector_format "T(%d %d) "

int main(void)
{
    // make a vector_t of things
    #define N 10
    vector_t a = vector_make(N, sizeof(T));

    for (int i = 0; i < 10*N; i+=1){

        // make something
        T b; b.x = i; b.y = 2*i;
        
        // append it to the vector
        a = maybe_grow(a);
        vector(a)[a.length++] = b;
    }
    
    for (size_t i = 0; i < a.length; i+=1){
        printf(vector_format, vector(a)[i].x, vector(a)[i].y );
    }

    vector_free(a);

    return 0;
}

#undef T
#undef vector
#undef vector_format
