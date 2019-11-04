
#include "array.h"

int main(int argc, char** argv){

	ARRAY a;
	array_init(&a);

	for (int i = 0; i < 10; i++) { array_add(&a, (char)48+i); }
	puts("\r\n\r\nChars");
	for (int i = 0; i < 10; i++) { printf("%c", (char)a.data[i]); }
	array_clear(&a);

	for (int i = 0; i < 10; i++) { array_add(&a, (double)(1.0/i)); }
	puts("\r\n\r\nFloats");
	for (int i = 0; i < 10; i++) { printf("%f ", (double)a.data[i]); }
	array_clear(&a);

	for (int i = 0; i < 10; i++) { array_add(&a, (int)987*i); }
	puts("\r\n\r\nInts");
	for (int i = 0; i < 10; i++) { printf("%d ", (int)a.data[i]); }
	array_clear(&a);

	for (int i = 0; i < 10; i++) { array_add(&a, (int8_t)1000*i); }
	puts("\r\n\r\nLittle Ints :)");
	for (int i = 0; i < 10; i++) { printf("%d ", (int8_t)a.data[i]); }
	array_clear(&a);


	return 0;
}




// int main(int argc, char** argv){

// 	int capacity = 1024;
// 	int stride = 8;
// 	void* a = malloc(capacity * stride);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		((int*)a)[i*stride] = 1000*i;
// 	}

// 	for (int i = 0; i < 10; i++)
// 	{
// 		printf("%d ", ((int*)a)[i*stride]);
// 	}
	
// 	return 0;
// }
