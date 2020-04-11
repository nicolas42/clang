#ifndef INTERFACE_H
#define INTERFACE_H

/* interface.h */
#include <stdio.h>

void method1(void);
void method2(int arg);



struct library {
    const int some_value;
    void (*method1)(void);
    void (*method2)(int);
    /* ... */
};

extern const struct library Library;
/* interface.h */


#endif


