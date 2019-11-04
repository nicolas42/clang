#ifndef INTARRAY_H
#define INTARRAY_H

typedef struct {
	char* data;
	int length;
	int capacity;
	int index;
} IntArray;

IntArray* intarray_init(IntArray* a);
IntArray* intarray_head(IntArray* a);
IntArray* intarray_tail(IntArray* a);
int intarray_is_head(IntArray* a);
int intarray_is_tail(IntArray* a);
IntArray* intarray_next(IntArray* a);
IntArray* intarray_back(IntArray* a);
IntArray* intarray_append(IntArray* a, int b);
IntArray* intarray_remove(IntArray* a, int index);
IntArray* intarray_insert(IntArray* a, int b, int index);
void intarray_print(IntArray* a);
IntArray* intarray_find(IntArray* a, int b);

#endif
