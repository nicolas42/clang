#ifndef STRING_H
#define STRING_H

typedef struct {
	char* data;
	int length;
	int capacity;
	int index;
} String;

String* string_init(String* a);
String* string_head(String* a);
String* string_tail(String* a);
int string_is_head(String* a);
int string_is_tail(String* a);
String* string_next(String* a);
String* string_back(String* a);
String* string_append(String* a, char b);
String* string_remove(String* a, int index);
String* string_insert(String* a, char b, int index);
void string_print(String* a);
String* string_find(String* a, char b);

#endif
