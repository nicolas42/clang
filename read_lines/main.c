#include <stdio.h>
#include <string.h>

int is_newline(char a){
	return (a == '\n' || a == '\r');
}

int main()
{

	// Read lines into a buffer
	FILE* fp;
	fp = fopen("main.c", "r");

	char buffer[1000000];
	int length_buffer = 0;
	int offsets[1000000];
	int length_offsets = 0;

	char line[100];
	while (fgets(line, 100, fp) != NULL){

		strcpy(buffer + length_buffer, line);
		offsets[length_offsets++] = length_buffer;

		length_buffer += strlen(line) + 1; // include null character ending

	}

	fclose(fp);


	for (int i = 0; i < length_offsets; i++){
		printf("{%s}", buffer + offsets[i]);
	}

	return 0;
}
