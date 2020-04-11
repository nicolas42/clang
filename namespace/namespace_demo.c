// clang namespace.c namespace_demo.c ; ./a.out

// To use namespaces in c define a struct full of function pointers
// and declare an external global instance of that struct 
// then initialize it in the .c file

#include "namespace.h"

int main(void)
{
	namespace.do_it();
	namespace.do_it_again();

	return 0;
}
