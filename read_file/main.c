#include <stdio.h>

int read_file(char *buff, int capacity, char *filename)
{

	int index = 0;
	FILE *fp = fopen("main.c", "r");

	// if at the end of the buffer or the file then return 
	// the number of bytes that have been index
	while (1)
	{
		int c = 0;

		c = fgetc(fp);
		if (c == EOF || (index >= (capacity - 1)))
		{
			// last place in buffer or file
			buff[index++] = '\0';
			break;
		}
		else
		{
			buff[index++] = c;
		}
	}

	fclose(fp);
	return index;
}

int main()
{

	int buffer_length = 1000000; // 1mb
	char buffer[buffer_length];

	// int written = read_file(buffer, buffer_length, "main.c");
	// printf("%s\r\n", buffer);
	// printf("%d/%d chars written \r\n", written, buffer_length);

	FILE *fp = fopen("main.c", "r");
    fread(buffer, 1000000, 1, fp);
	printf("%s", buffer);

	return 0;
}
