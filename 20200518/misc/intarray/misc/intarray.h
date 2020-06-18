#ifndef INTARRAY_H
#define INTARRAY_H

typedef struct {
	int* data;
	int length;
	int capacity;
	int index;
} INTARRAY;

INTARRAY* intarray_init(INTARRAY* a);
INTARRAY* intarray_head(INTARRAY* a);
INTARRAY* intarray_tail(INTARRAY* a);
int intarray_is_head(INTARRAY* a);
int intarray_is_tail(INTARRAY* a);
INTARRAY* intarray_next(INTARRAY* a);
INTARRAY* intarray_back(INTARRAY* a);
INTARRAY* intarray_append(INTARRAY* a, int b);
INTARRAY* intarray_remove(INTARRAY* a, int index);
INTARRAY* intarray_insert(INTARRAY* a, int b, int index);
void intarray_print(INTARRAY* a);
INTARRAY* intarray_find(INTARRAY* a, int b);

#endif
