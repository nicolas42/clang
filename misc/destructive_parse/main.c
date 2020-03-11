// push(){git add . && git commit -m $1 && git push}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "mymath.h"

static int WORDS_INITIAL_CAPACITY = 10;
static int READ_FILE_INITIAL_CAPACITY = 100;


void read_file(char** a, FILE* file) {

  int index, capacity, value;

  index = 0;
  capacity = READ_FILE_INITIAL_CAPACITY;
  (*a) = malloc(capacity * sizeof(char));

  while (1) {

      if (index == capacity){
        capacity *= 2;
        (*a) = realloc((*a), capacity * sizeof(char));
      }

      value = fgetc(file);
      if (value == EOF) {
          (*a)[index] = '\0';
          break;
      } else {
          (*a)[index] = (char)value;
          index += 1;
      }
  }
}

// typedef struct {
// 	int length;
// 	int capacity;
// 	int index;
// } ArrayInfo;

// void ArrayInfo_init(ArrayInfo* a){
// 	a->index = 0;
// 	a->length = 0;
// 	a->capacity = 2;
// }

void destructive_parse(
    char*** b, int* length, char* a, int(*fn)(int) ) {

  int capacity = WORDS_INITIAL_CAPACITY;
  (*b) = malloc(capacity * sizeof(int));
  int index = 0;

  for (int i = 0; a[i] != '\0'; i += 1){

    // Double size if necessary
    if (index == capacity) {
        capacity *= 2;
        (*b) = realloc((*b), sizeof(char) * capacity);
    }

    // Turn spaces to null
    if ( fn(a[i]) ){
        a[i] = '\0';
    }
    // Note down index at null non-null junctions 
    // or at a non-null character which is at the head of a series
    if ( (a[i] != '\0') && (a[i-1] == '\0' || i == 0) ){
        (*b)[index] = a+i;
        (*length)++;
        index++;
    }
  }
}

void parse_words(char*** b, int* length, char* a) {

    int capacity = WORDS_INITIAL_CAPACITY;
    (*b) = malloc(capacity * sizeof(int));
    int index = 0;
    int i;
    for (i = 0; a[i] != '\0'; i += 1){

        // Double size if necessary
        if (index == capacity) {
            capacity *= 2;
            (*b) = realloc((*b), sizeof(char) * capacity);
        }

        // Turn spaces to null
        if ( isspace(a[i]) ){
            a[i] = '\0';
        }
        // Note down index at null non-null junctions 
        // or at a non-null character which is at the head of a series
        if ( (a[i] != '\0') && (a[i-1] == '\0' || i == 0) ){
            (*b)[index] = a+i;
            (*length)++;
            index++;
        }
    }
}

int isnewline(int a){
  if ((char)a == '\n' || (char)a == '\r'){
    return 1;
  } else {
    return 0;
  }
}

int iscolon(int a){
  if ((char)a == ':'){
    return 1;
  } else {
    return 0;
  }
}

int main()  
{  

//   if (0){
//     x = 3;
//     printf("x: %d\n", x);
//     printf("x^2: %d\n", mymath_square(x));
//   }

  if (1){

    // Read the file into a string
    FILE *file;
    char* string;

    file = fopen("record", "r");
    read_file(&string, file);
    fclose(file);

    // === Destructively parse string into words === 
    char* string2;
    char** words; 
    int words_length;

    // Make a copy of the string
    string2 = malloc(strlen(string) * sizeof(char));
    memcpy(string2, string, strlen(string)+1);
    
    // Find where the words begin and change delimiters to nulls
    destructive_parse(&words, &words_length, string2, isnewline);

    // Print the file and words
    printf("%s", string);
    for (int i = 0; i < words_length; i += 1){
      printf("{%s} ", words[i]);
    }
    printf("\n");
    

    // Free stuff
    free(string);
    free(string2);
    free(words);

  }

  return 0;  
}
