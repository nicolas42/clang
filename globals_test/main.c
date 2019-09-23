// push(){git add . && git commit -m $1 && git push}

#include <stdio.h>
#include <stdlib.h>
#include "mymath.h"


struct Date {
  int day;
  int month;
  int year;
};

struct Person {
  char name[20];
  struct Date birthday;
  float salary;
  char job[20];
};

static int x; // file scope

char* read_file(char* data, FILE* file) {

    int length = 100;
    malloc(sizeof(char) * length);
    int index = 0;
    int value = 0;

    while (1) {

        if (index == length) {
            length = length * 2;
            data = realloc(data, sizeof(char) * length);
        }

        value = fgetc(file);
        if (value == EOF) {
            data[index] = '\0';
            return data;
        } else {
            data[index] = (char)value;
            index += 1;
        }
    }
}


int main()  
{  

  if (1){
    x = 3;
    printf("x: %d\n", x);
    printf("x^2: %d\n", mymath_square(x));
  }


  FILE *file;
  char* string;


  file = fopen("record", "r");
  read_file(string, file);
  
  printf("%s", string);

  fclose(file);  


  return 0;  
}


