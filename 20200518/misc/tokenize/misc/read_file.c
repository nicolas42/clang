
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
