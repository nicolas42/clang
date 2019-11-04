#ifndef THING_H
#define THING_H

#define THING_SIZE 30  // size of a thing string
#define THING_FORMAT "[%d %d]"
#define THING_SEPARATOR " "  // for multiple strings

typedef struct {
	int a;
	int b;
} Thing;

typedef struct {
	Thing* values;
	int length;
	int capacity;
	int index;
} Things;

void usage();
void thing_make(Thing* thing, int a, int b);
int thing_is_equal(Thing a, Thing b);
int thing_string(char* out, Thing thing);
void thing_print(Thing thing);
void things_init(Things* things);
void things_head(Things* things);
void things_tail(Things* things);
int things_is_head(Things things);
int things_is_tail(Things things);
void things_next(Things* things);
void things_back(Things* things);
void things_append(Things* things, Thing thing);
void things_remove(Things* things, int index);
void things_insert(Things* things, Thing thing, int index);
int things_find(Things things, Thing thing);
void things_string(char** buffer, Things things);
void things_print(Things things);

// void things_test_dynamic_usage(char** buffer);
// void things_test_static_usage(void);


#endif
