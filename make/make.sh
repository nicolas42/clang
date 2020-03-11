cat $0

# flags
# -Isrc -std=c99 -Wall -Wextra -Wpedantic -Wfatal-errors -fPIC -g -fsanitize=address 

# make library
gcc -c src/*.c \
-Isrc -std=c99 -Wall -Wextra -Wpedantic -Wfatal-errors -fPIC -g -fsanitize=address
ar rcs lib.a *.o
rm *.o

# make demo functions
gcc lib.a examples/demo-functions.c -o demo-functions \
-Isrc -std=c99 -Wall -Wextra -Wpedantic -Wfatal-errors -fPIC -g -fsanitize=address 

# make mandelbrot generator
gcc src/mandelbrot.c -o python/mandelbrot.so \
-Isrc -std=c99 -Wall -Wextra -Wpedantic -Wfatal-errors -fPIC -g -shared #address sanitizer errors for some reason
python python/mandelbrot.py
# open mandelbrot.ppm 
