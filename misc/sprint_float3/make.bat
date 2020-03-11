mkdir bin
gcc -c -Wall -pedantic -std=c99 -o bin/main.o main.c
gcc -Wall -pedantic -std=c99 -o main bin/*.o
main
