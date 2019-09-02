int mymath_timesTwo(int n) {
	return n * 2;
}

int mymath_square(int n) {
	return n * n;
}

char* mymath_evenOddMessage(int n) {
	if (n % 2 == 0) {
		return "Even";
	} else {
		return "Odd";
	}
}