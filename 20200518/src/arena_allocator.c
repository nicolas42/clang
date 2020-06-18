#include "arena_allocator.h"
// #define DEBUG

static void* arena;
static size_t arena_length;
static size_t arena_capacity;


// === Arena Allocator =============

void arena_make(size_t cap)
{
    arena_length = 0;
    arena_capacity = cap;
    arena = malloc(cap);
}

void* arena_allocate(size_t allocated)
{
    void* offset = (char*)arena + arena_length;
    arena_length += allocated;

    // realloc on overflow
    if (arena_length > arena_capacity){

// #ifdef DEBUG
//     printf("ALLOC!!! length: %lu capacity: %lu\n", arena_length, arena_capacity*2);
// #endif

        arena_capacity *= 2;
        arena = realloc(arena, arena_capacity);
    }

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
