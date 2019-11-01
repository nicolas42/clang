#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "mystring.h"


int read_file(char* filename)
{
        char c = '\0';
        FILE* file = fopen(filename,"r");

        while(1){
                c = fgetc(file);
                if (c == EOF){
                        break;
                } else {
                    	putc(c, stdout);

                }
        }

        return 0;
}

int main () {

	char filename[100] = "main.c";
	int buffer_capacity = 1000000;
	char buffer[buffer_capacity];
	buffer_length = 0;

	FILE* fp = fopen("main.c", "r");

	// if get to the end of the buffer or the end of the file 
	// then write a null and return
	// otherwise just copy the character

        while(1){
                c = fgetc(file);
		
		if (buffer_length >= (buffer_capacity - 1)){
			// out of space
			buffer[buffer_length++] = '\0';
			return 0;
		}
                if (c == EOF){
			buffer[buffer_length++] = '\0';
			return buffer_length;
                        break;
                } else {
			buffer[buffer_length++] = c;

                }
        }


	return 0;
}
