#ifndef FLOATARRAY_H
#define FLOATARRAY_H

typedef struct {
	char* data;
	int length;
	int capacity;
	int index;
} FloatArray;

FloatArray* float_init(FloatArray* a);
FloatArray* float_head(FloatArray* a);
FloatArray* float_tail(FloatArray* a);
int float_is_head(FloatArray* a);
int float_is_tail(FloatArray* a);
FloatArray* float_next(FloatArray* a);
FloatArray* float_back(FloatArray* a);
FloatArray* float_append(FloatArray* a, double b);
FloatArray* float_remove(FloatArray* a, int index);
FloatArray* float_insert(FloatArray* a, double b, int index);
void float_print(FloatArray* a);
FloatArray* float_find(FloatArray* a, double b);

#endif
