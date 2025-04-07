#include <iostream>

#define MAX 92 // Largest n for which F(n) fits in a long


long Fibonacci(int position) {
	long a = 0, b = 1;

	if (position == 0)
		return 0; // a
	else if (position == 1)
		return 1; // b
	else {
		for (int i = 2; i <= position; i++) {
			int next = a + b;
			a = b;
			b = next;
		}

		return b;
	}
}


int main() {
	int position = 39;

	if (position < 0 || position > MAX) {
		std::cerr << "Error: position must be between 0 and " << MAX << '\n';
		return 1;
	}

	long result = Fibonacci(position);
	std::cout << "Fibonacci number at position " << position << " is " << result << '\n';

	return 0;
}
