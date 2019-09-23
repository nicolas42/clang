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

void parse_string(char* arg, int* offsets, int* arg_length) {

  int length = *arg_length;
  offsets = realloc(offsets, sizeof(int) * length);
  int index = 0;
  
  for (int i = 0; arg[i] != '\0'; i += 1){

    if (i == length) {
        length = length * 2;
        offsets = realloc(offsets, sizeof(char) * length);
    }

    // if the value under the input index is a non-whitespace character 
    // and the previous char was a whitespace char OR we are at the head of the input
    // then note down the beginning offset of the word

    if ( isspace(arg[i]) ){
      arg[i] = '\0';
    }

    if ( (arg[i] != '\0') && (arg[i-1] == '\0' || i == 0) ){
      offsets[index] = i;
      index++;
    }

  }
  *arg_length = index;
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

    int* offsets = malloc(2*sizeof(int));
    int length = 100;
    parse_string(offsets, offsets, &length);

    printf("%d\n", offsets[0]);
    printf("%d\n", offsets[1]);
    printf("%d\n", offsets[2]);

    printf("%s\n", string + 0);
    printf("%s\n", string + 6);

    // printf("%s", string);
    fclose(file);  
  }

  return 0;  
}



// int read_line(char* result, FILE* file) {
//     int size = INIT_LINE_LENGTH;
//     char* result = realloc(sizeof(char) * size);
//     int position = 0;
//     int next = 0;

//     while (1) {

//         if (position == size) {
//             size = size * 2;
//             // printf("\nREALLOC\n");
//             result = realloc(result, sizeof(char) * size);
//         }
//         next = fgetc(file);
//         if (next == EOF || next == '\n') {
//             result[position] = '\0';
//             return result;
//         } else {
//             result[position++] = (char)next;
//         }
//     }
// }




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
