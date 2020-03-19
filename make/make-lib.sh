cat $0

# make library
gcc -c src/*.c \
-Isrc -std=c99 -Wall -Wextra -Wpedantic -Wfatal-errors -fPIC -g -fsanitize=address
ar rcs lib.a *.o
rm *.o