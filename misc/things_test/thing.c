#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thing.h"


void usage(){
	fprintf(stderr, "Usage: thing [numberOfThings]\n");
	exit(1);
}

void thing_make(Thing* thing, int a, int b) {
	thing->a = a;
	thing->b = b;
}

int thing_is_equal(Thing a, Thing b){
	return a.a == b.a && a.b == b.b;
}

int thing_string(char* out, Thing thing){
	int n = sprintf(out, THING_FORMAT, thing.a, thing.b);	
	return n;
}

void thing_print(Thing thing){
	char str[THING_SIZE];
	thing_string(str, thing);
	printf("%s", str);
}


void things_init(Things* things){
	things->index = 0;
	things->length = 0;
	things->capacity = 2;
	things->values = malloc(things->capacity * sizeof(Thing));
}

void things_head(Things* things){
	things->index = 0;
}

void things_tail(Things* things){
	things->index = things->length;
}

int things_is_head(Things things){
	return things.index == 0;
}

int things_is_tail(Things things){
	return things.index == things.length;
}

void things_next(Things* things){
	if (!things_is_tail(*things)){
		things->index++;
	}
}

void things_back(Things* things){
	if (!things_is_head(*things)){
		things->index--;
	}
}

void things_append(Things* things, Thing thing){
	
	if (things->length == things->capacity){
		things->capacity = 2 * things->capacity;
		things->values = realloc(things->values, things->capacity * sizeof(Thing));
	}
	things->values[things->length] = thing;
	things->length++;
}

void things_remove(Things* things, int index){
	
	for (int i = index; i <= things->length - 2; ++i)
		things->values[index] = things->values[index + 1];
	things->length--;
}

void things_insert(Things* things, Thing thing, int index){
	
	// append one thing to ensure allocations are done
	things_append(things, thing);
	
	for (int i = index; i <= things->length - 2; ++i)
		things->values[index + 1] = things->values[index];
	
	// Actually set the thing
	things->values[index] = thing;
	things->length++;
}

int things_find(Things things, Thing thing){

	for (int i=things.index; i<things.length; i+=1){
		if (thing_is_equal(things.values[i], thing)){
			return i;
		}
	}
	return -1;
}

void things_string(char** buffer, Things things){
	// assume need THING_SIZE bytes max for serialized thing
	*buffer = realloc(*buffer, things.length * THING_SIZE); 
	int offset = 0;
	int n = -1;
	int m = -1;
	
	for (int i=0; i<things.length; i+=1){
		n = thing_string(*buffer + offset, things.values[i]);
		offset += n;
		m = sprintf(*buffer + offset, THING_SEPARATOR);
		offset += m;
	}
}

void things_print(Things things){
	char* str = malloc(8);
	things_string(&str, things);
	printf("%s", str);
	free(str);
}
