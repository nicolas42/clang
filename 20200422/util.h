#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <string.h>
// #include <ctype.h>
#include <stdlib.h>

// Parse words by noting down the starting positions of words 
// and changing spaces to null characters


typedef struct string {
	size_t length;
	size_t allocated;
	char* data;
} string;

typedef struct strings {
	size_t length;
	size_t allocated;
	char** data;
} strings;


string string_make(size_t n);
void string_free(string f);
void string_maybe_grow(string* f);

string read_file(char *filename);

strings strings_init(void);
strings strings_make(size_t length);
void strings_free(strings f);
void strings_maybe_grow(strings* f);
void strings_add(strings* f, char* a);
string string_copy(string a);

// strings split_lines_destructive(char* str_arg);
void demo_split_destructive(void);
double min(double a, double b);
strings split_destructive(char* a, char* split_chars);

string string_make(size_t n)
{
	string f;
	f.length = 0;
	f.allocated = n;
	f.data = malloc(n);
	return f;
}

string string_copy(string a)
{
	string b;
	b.length = a.length;
	b.allocated = a.allocated;
	b.data = malloc(b.allocated*sizeof(char*));
	strcpy(b.data, a.data);
	return b;
}

void string_free(string f)
{
	free(f.data);
}

void string_maybe_grow(string* f)
{
	if (f->length == f->allocated){
		f->allocated *= 2;
		f->data = realloc(f->data, f->allocated);
	}
}

string read_file(char *filename)
{
	#define error_size 200
	string f = string_make(1000);

	FILE *fp;
	int c;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		char err[error_size];
		snprintf(err, error_size, "Error in opening file %s", filename);
		perror(err);
		return f;
	}

	while (1) {
		c = fgetc(fp);
		if (feof(fp)) { 
			f.data[f.length] = '\0';
			f.length += 1;
			break; 
		}
		f.data[f.length] = (char)c;
		f.length += 1;
		string_maybe_grow(&f);
	}
	fclose(fp);

	return f;
	#undef error_size
}

strings strings_init(void)
{
	strings f;
	f.length = 0;
	f.allocated = 1000;
	f.data = malloc(1000*sizeof(char*));
	return f;
}

strings strings_make(size_t n)
{
	strings f;
	f.length = 0;
	f.allocated = n;
	f.data = malloc(n*sizeof(char*));
	return f;
}

void strings_free(strings f)
{
	free(f.data);
}

void strings_maybe_grow(strings* f)
{
	if (f->length == f->allocated){
		f->allocated *= 2;
		f->data = realloc(f->data, f->allocated*sizeof(char*));
		printf("GROW!!!\n");
	}
}

void strings_add(strings* f, char* a)
{
	strings_maybe_grow(f);
	f->data[f->length] = a;
	f->length += 1;
}

// strings split_lines_destructive(char* a)
// {
// 	strings lines = strings_make(10000);

// 	strings_add(&lines, &(a[0]));

// 	size_t strlen_a = strlen(a);
// 	printf("strlen(a) %lu\n", strlen(a));

// 	for (size_t i = 1; i < strlen_a; i++){

// 		if ( a[i] == '\n' || a[i] == '\r' ) {
// 			a[i] = '\0';		
// 		}
// 	}

// 	for (size_t i = 1; i < strlen_a; i++) {

// 		if (a[i-1] == '\0' && a[i] != '\0') {
// 			strings_add(&lines, &(a[i]));
// 		}
// 	}

// 	return lines;
// }


double min(double a, double b)
{
	if (a < b ){
		return a;
	}
	return b;
}

strings split_destructive(char* a, char* split_chars)
{
	strings lines = strings_make(10000);

	strings_add(&lines, &(a[0]));

	size_t strlen_a = strlen(a);
	printf("strlen(a) %lu\n", strlen(a));

	for (size_t i = 1; i < strlen_a; i++){

		for (size_t j = 0; j < strlen(split_chars); j++)
		{
			if ( a[i] == split_chars[j] ){ a[i] = '\0'; break; }
		}
	}

	for (size_t i = 1; i < strlen_a; i++) {

		if (a[i-1] == '\0' && a[i] != '\0') {
			strings_add(&lines, &(a[i]));
		}
	}

	return lines;
}



void demo_split_destructive(void)
{
	string f = read_file("tokenize.h");
	strings tokens = split_destructive(f.data, "\n\r\t ");

	for (size_t i = 0; i < min(10, tokens.length); i++){
		printf("{%s} ", tokens.data[i]);
	}
}


// typedef struct slice { int offset ; int length; } slice;

// typedef struct slices {
// 	size_t length;
// 	size_t allocated;
// 	slice* data;
// } slices;


#endif
