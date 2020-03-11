#ifndef PAIR_ARRAY_H
#define PAIR_ARRAY_H

struct pair {
	int x; int y;
};

void pair_make(struct pair *a, int x, int y);

typedef struct {
	struct pair *data;
	int length;
	int allocated;
} pair_array;

pair_array* pair_array_init(pair_array* a);
pair_array* pair_array_add(pair_array* a, struct pair b);



#endif
