cat $0
clang -c -Isrc -lm `ls src/*.c `
ar rcs lib.a *.o
rm *.o
