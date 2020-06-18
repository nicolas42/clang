#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thing.h"


void things_test_dynamic_usage(){

	Things xs; // dynamic things
	things_init(&xs); // malloc .values
	Thing x;
	int i;
	
	for (i=0; i<10; i+=1){
		thing_make(&x, i, i);
		things_append(&xs, x);
	}

	things_print(xs);
	xs.values[0] = xs.values[1];
	xs.values[2] = xs.values[1];
	things_print(xs);
	things_remove(&xs, 3);
	things_print(xs);
	
	printf("\nFind {5,5}\n");
	thing_make(&x, 5,5);
	i=things_find(xs, x);
	thing_print(xs.values[i]);
	
	free(xs.values);
}

void things_test_static_usage(void){
	int i = 0;
	int LENGTH = 5;
	Thing things[LENGTH];

	for (i = 0; i < LENGTH; ++i)
		thing_make(&things[i], rand(), rand());

	for (i = 0; i < LENGTH; ++i){
		thing_print(things[i]);
		printf(THING_SEPARATOR);
	}
	printf("\n");
}

int main(int argc, char** argv){
	
	int N = 0;

	// Argument Validation
	switch (argc){
		case 2:
			N = atoi(argv[1]);
			break;
		case 1:
			N = 5; // default
			break;
		default:
		    usage();
			break;
	}

	// char* buffer = malloc(sizeof(char));

	printf("\nTest Dynamic Usage\n");
	things_test_dynamic_usage();
	
	printf("\nTest Static Usage\n");
	things_test_static_usage();
	
	// free(buffer);
	


	printf("\nTest asprintf\n");
	char* test = malloc(1);
	asprintf(&test, "Hello you bastard\n"); // malloc

	puts(test);
	free(test);
	
	
	return 0;
}

/*

	// Predicted values
	int pl = 8;
	int p[pl] = {0,0,0,0,2,2,4,4};
	
	for (i = 0; i < pl; i+=2){
		thing_make(&tmp, p[i], p[i+1]);
		if (!thing_is_equal(d.values[i/2], tmp)){
			printf("Failed Test\n");
		}
	}


	// Test Code	
	// Assign one struct to another - testing
	// thing[0] = thing[1];// char strings[2][100] = {"Hello\0", "Goodbye\0"};
	
	// Make N things
	int N = 100;
	
void remove_card(Cards* cards, int cardNumber) {
    // top of cards is at cards.length
    int cardIndex = cards->length - 1 - cardNumber;
    // printf("%d\n", cardIndex);
    for (int i = cardIndex; i < cards->length; ++i) {
        cards->values[i] = cards->values[i + 1];
    }
    cards->length = cards->length - 1;
}


int data_read(Card* card, char* line) {
    // needs error checking
    sscanf(line, "%c:%d:%d,%d,%d,%d", &(card->discount), &(card->points), 
            card->tokens + PURPLE, card->tokens + BROWN, 
            card->tokens + YELLOW, card->tokens + RED);
    return 0;
}

int read_cards_file(Cards* cards, char* filename) {
    char* line;
    FILE* cardsFile = fopen(filename, "r");
    while (line = read_line(cardsFile), line[0] != '\0') {
        Card card;
        read_card(&card, line);
        append_card(cards, &card);
    }
    fclose(cardsFile);
    return 0;
}




int read_line(char* result, FILE* file) {
    int size = INIT_LINE_LENGTH;
    char* result = realloc(sizeof(char) * size);
    int position = 0;
    int next = 0;

    while (1) {

        if (position == size) {
            size = size * 2;
            // printf("\nREALLOC\n");
            result = realloc(result, sizeof(char) * size);
        }
        next = fgetc(file);
        if (next == EOF || next == '\n') {
            result[position] = '\0';
            return result;
        } else {
            result[position++] = (char)next;
        }
    }
}

*/

