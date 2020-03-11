#include "mymath.h"

int mymath_times_two(int n) {
	return n * 2;
}

int mymath_square(int n) {
	return n * n;
}

char* mymath_even_odd_message(int n) {
	if (n % 2 == 0) {
		return "Even";
	} else {
		return "Odd";
	}
}
