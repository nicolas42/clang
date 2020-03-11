#ifndef DARRAY_H
#define DARRAY_H

typedef struct {
	double* data;
	int length;
	int capacity;
	// int index;
} DARRAY;

DARRAY* darray_init(DARRAY* a);
DARRAY* darray_add(DARRAY* a, double b);

#endif
