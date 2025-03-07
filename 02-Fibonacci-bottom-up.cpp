#include <iostream>

#define MAX 92 // Largest n for which F(n) fits in a long
long storage[MAX + 1];


int Fibonacci(int position) {
	storage[0] = 0;
	storage[1] = 1;

	for (int i = 2; i <= position; i++)
		storage[i] = storage[i - 1] + storage[i - 2];

	return storage[position];
}


int main() {
	int position = 10;

	if (position < 0 || position > MAX) {
		std::cerr << "Error: position must be between 0 and " << MAX << '\n';
		return 1;
	}

	long result = Fibonacci(position);
	std::cout << "Fibonacci number at position " << position << " is " << result << '\n';

	return 0;
}
