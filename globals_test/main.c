// push(){git add . && git commit -m $1 && git push}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

char* read_file(FILE* file) {

  int length = 100;
  char* data = malloc(sizeof(char) * length);
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

int* parse_string(char* arg, int* length_arg) {

  int length = *length_arg;
  int* offsets = malloc(sizeof(int) * length);
  int index = 0;
  int is_in_word = 0;
  
  for (int i = 0; arg[i] != '\0'; i += 1){

    if (i == length) {
        length = length * 2;
        offsets = realloc(offsets, sizeof(char) * length);
    }

    // if the value under the input index is a non-whitespace character 
    // and the previous char was a whitespace char OR we are at the head of the input
    // then note down the beginning offset of the word


    if ( (!isspace(arg[i])) && (i == 0 || isspace(arg[i-1])) ){
      offsets[index] = i;
      index++;
      is_in_word = 1;
    }
    if ( (i != 0) && ( (isspace(arg[i]) || arg[i] == '\0') && (!isspace(arg[i-1])) ) ) {
      offsets[index] = i;
      index++;
      is_in_word = 0;
    }

    if ( isspace(arg[i]) ){
      arg[i] = '\0';
    }

  }
  *length_arg = index;
  return offsets;
}


int main()  
{  

  if (1){
    x = 3;
    printf("x: %d\n", x);
    printf("x^2: %d\n", mymath_square(x));
  }

  if (1){
    FILE *file;
    char* string;

    file = fopen("record", "r");
    string = read_file(file);

    int length = 100;
    int* offsets = parse_string(string, &length);

    printf("%s", string + offsets[0]);
    printf("%s", string + offsets[2]);
    printf("%s", string + offsets[4]);
    printf("%s", string + offsets[6]);
    printf("%s", string + offsets[8]);

    // printf("%s", string);
    fclose(file);  
  }

  return 0;  
}



// struct Bytes {
//   int length;
//   char* offsets;
//   int index;
//   int is_in_word;
// };

// int bytes_init(struct Bytes* arg){

//   arg->length = 100;
//   arg->offsets = malloc(sizeof(char) * arg->length);
//   arg->index = 0;
//   arg->is_in_word = 0;

// }

  // Bytes offsets;
  // bytes_init(&offsets);
