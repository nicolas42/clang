// cls & cl print_file.c & print_file 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NEWLINE '\n'
#define INITIAL_STRING_SIZE 1000
#define FILENAME "file.txt"
#define LINE_NUMBERS_ON yes

int read_file()
{
	uint32_t line_number = 0;
	char c = '\0';
	FILE* file = fopen(FILENAME,"r");

	printf("\n# %s\n", FILENAME);
	printf("=========================\n");

#ifdef LINE_NUMBERS_ON
	// Print line number
	printf("%d\t", line_number);
	line_number++;
#endif

	// Print all chars.  If EOF break, 
	// if newline then print a line number after it
	while(1)
	{
		c = fgetc(file);
		if (c == EOF){

			break;
		
		}
#ifdef LINE_NUMBERS_ON
		 else if (c == NEWLINE){

			putc(c, stdout);
			printf("%d\t", line_number);
			line_number++;

		}
#endif
		 else {

			putc(c, stdout);

		}
	}

	return 0;
}

int read_1000(char* filename)
{
	FILE* file = fopen(filename, "r");
	char contents[INITIAL_STRING_SIZE];

	fgets(contents, INITIAL_STRING_SIZE, file);
	printf("%s\n", contents);

	return 0;
}

int main(int argc, char** argv){

	read_file();

	return 0;
}