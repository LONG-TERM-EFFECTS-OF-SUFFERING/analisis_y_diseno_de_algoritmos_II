#include <iostream>
#include <vector>

#define MAX 92 // Largest n for which F(n) fits in a long
#define UNKNOWN -1 // Contents denote an empty cell
std::vector <long> storage(MAX + 1, UNKNOWN);


int Fibonacci_helper(int position) {
	if (storage[position] == UNKNOWN)
		storage[position] = Fibonacci_helper(position - 1) + Fibonacci_helper(position - 2);

	return storage[position];
}

int Fibonacci(int position) {
	storage[0] = 0;
	storage[1] = 1;

	for (int i = 2; i < MAX; i++)
		storage[i] = UNKNOWN;

	return Fibonacci_helper(position);
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
