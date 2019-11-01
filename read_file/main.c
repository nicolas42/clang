#include <stdio.h>

int read_file(char *buff, int N, char *filename)
{

	// char filename[100] = "main.c";
	// int N = 1000000;
	// char buff[N];

	int i = 0;
	int c = 0;
	FILE *fp = fopen("main.c", "r");

	// if get to the end of the buff or the end of the file
	// then write a null and return
	// otherwise just copy the character

	while (1)
	{
		c = fgetc(fp);

		if (c == EOF || (i >= (N - 1)))
		{
			// last place in buffer or file
			buff[i++] = '\0';
			break;
		}
		else
		{
			buff[i++] = c;
		}
	}

	fclose(fp);
	return i;
}

int main()
{

	// printf("Hello world\r\n");

	// Read file into a static buffer
	int capacity = 5;
	char buffer[capacity];
	int written = read_file(buffer, capacity, "main.c");

	printf("%s\r\n", buffer);
	printf("%d/%d chars written \r\n", written, capacity);

	return 0;
}
