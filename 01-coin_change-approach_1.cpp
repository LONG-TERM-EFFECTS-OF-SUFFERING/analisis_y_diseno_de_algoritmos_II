#include <iostream>


int* approach_1(int denominations[], int n, int amount) {
	int* solution = new int[n]();

	for (int i = n - 1; i >= 0; i--) {
		solution[i] = amount / denominations[i];
		amount -= solution[i] * denominations[i];
	}

	return solution;
}


int main() {
	int denominations[] = { 1, 5, 10, 25 };
	int amount = 30;
	int n = sizeof(denominations) / sizeof(int);
	int* result = approach_1(denominations, n, amount);

	for (int i = 0; i < 4; i++)
		std::cout << result[i] << " ";
	std::cout << std::endl;

	delete[] result;

	return 0;
}
