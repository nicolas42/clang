/*
Generic resizeable array.
It's a struct with length parameters and a char pointer where the data goes.
To use it with arbitrarily data types

Usage
change the typedef to your type
typedef test_struct T;


#define array(i) ( *((T*)a.data + i) )


clang a.c -Weverything -Wno-cast-align ; ./a.out
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct array_t {
	size_t length;
	size_t allocated;
	char* data;
    size_t size;
} array_t;

array_t array_make(size_t n, size_t s);
void array_free(array_t f);
array_t maybe_grow(array_t f);


typedef struct test_struct {
    int x; int y;
} test_struct;

void print_test_struct(test_struct a)
{
    printf("test_struct(%d %d) ", a.x, a.y);
}

typedef test_struct T;
#define array(i) ( *((T*)a.data + i) )
#define array_format "%llu "

int main(void)
{
    #define n 10
    array_t a = array_make(n, sizeof(T));

    for (int i = 0; i < 10*n; i+=1){

        test_struct t;
        t.x = i; t.y = 2*i;

        array(i) = t;
        a.length += 1;
        a = maybe_grow(a);
    }
    
    for (size_t i = 0; i < a.length; i+=1){
        print_test_struct(array(i));
        // printf(array_format, array(i) );
    }

    array_free(a);

    return 0;
}


array_t array_make(size_t n, size_t s)
{
    // make sure alignment is good. 
    // so an integer number of datas fits inside
    while ( n % s != 0 ){ n += 1; }

	array_t f;
    f.size = s;
	f.length = 0;
	f.allocated = n;
	f.data = malloc(n*s);
	return f;
}

void array_free(array_t f)
{
	free(f.data);
}

array_t maybe_grow(array_t f)
{
	if (f.length == f.allocated){
		f.allocated *= 2;
		f.data = realloc(f.data, f.allocated * f.size);
        puts("woohoo");
	}
    return f;
}


