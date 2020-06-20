src contains object files which are compiled to lib.a
examples and demos contain main functions which use lib.a

run demos like this

1. make lib.a

	make

2. compile code which uses lib.a

	clang demos/demo-mandelbrot.c lib.a

3. run the thing, test it, and so on

	./a.out
	open mandelbrot.ppm


Once lib.a is created it can be reused obviously, unless you change it.

