# push ( ) { git add . ; git commit -m $1 ; git push }

flags="-Isrc -std=c99 -Wall -Wextra -Wpedantic -Wfatal-errors -fPIC -g -fsanitize=address -lm"

all: library #demo mandelbrot

library:
	clang $(echo $flags) -c src/*.c
	ar rcs lib.a *.o
	rm *.o

demo:
	clang $(echo $flags) lib.a examples/demo-functions.c -o demo-functions

mandelbrot:
	clang src/mandelbrot.c -o python/mandelbrot.so \
	-Isrc -std=c99 -Wall -Wextra -Wpedantic -Wfatal-errors -fPIC -g -shared #address sanitizer errors for some reason
	python python/mandelbrot.py
	# open mandelbrot.ppm
