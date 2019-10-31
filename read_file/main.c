#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int read_file1(char* filename)
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


int main(int argc, char **argv)
{
        printf("Hello World\r\n");
        read_file1("main.c");
        return 0;
}

