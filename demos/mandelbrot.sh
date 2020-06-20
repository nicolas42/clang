cat $0
clang demos/mandelbrot_main.c lib.a -Isrc 
./a.out 400 400 
open out.ppm

