/*
clang -Weverything a.c arena_allocator.h types.h ; ./a.out
*/

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "arena_allocator.h"

#include "util.h"

typedef struct Book {
   char*  title;
   char*  author;
   char*  subject;
   u32    book_id;
   u32    padding;
} Book;

void print_book(struct Book book);
Book make_book(char* title, char* author, char* subject, u32 book_id);


static const char* const book_format = "Book{ %s %s %s %d }\n";


void print_book(struct Book book)
{
    printf( book_format, book.title, book.author, book.subject, book.book_id );
}

Book make_book(char* title, char* author, char* subject, u32 book_id)
{
    Book b;
    b.title = arena_allocate(100);
    b.author = arena_allocate(100);
    b.subject = arena_allocate(100);

   strcpy( b.title, title);
   strcpy( b.author, author); 
   strcpy( b.subject, subject);
    b.book_id = book_id;

   return b;
}



int main( )
{

    arena_init();

    Book *books = (Book*)arena_allocate(100*sizeof(Book));

    books[0] = make_book("C Programming", "Nuha Ali", "C Programming Tutorial", 6495407);
    books[1] = make_book("Telecom Billing", "Zara Ali", "Telecom Billing Tutorial", 6495700);

    print_book(books[0]);
    print_book(books[1]);

    books[1] = books[0];

    print_book(books[0]);
    print_book(books[1]);


    // tokenize_demo();

    demo_split_destructive();
    
   return 0;
}

