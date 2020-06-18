#ifndef INTARRAY_H
#define INTARRAY_H

typedef struct {
	int* data;
	int length;
	int capacity;
	int index;
} INTARRAY;

INTARRAY* intarray_init(INTARRAY* a);
INTARRAY* intarray_add(INTARRAY* a, int b);

#endif
