cat $0
cd ../
gcc src/mandelbrot.c -o python/mandelbrot.so   -fPIC -shared -std=c99 -pedantic -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -g   #-fsanitize=address
python python/mandelbrot.py
open mandelbrot.ppm 
