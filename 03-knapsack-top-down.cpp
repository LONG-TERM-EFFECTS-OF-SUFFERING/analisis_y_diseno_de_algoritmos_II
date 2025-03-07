#include <algorithm>
#include <iostream>

#define UNKNOWN -1

int m, n;
int** storage;
int* solution;


int knapsack_helper(int capacity, int items, int b[], int w[]) {
	if (items == 0) // items <= 0
		return 0; // Base case: no items left
	else {
		int i = capacity - 1, j = items - 1;
		if (storage[i][j] == UNKNOWN) {
			int benefit = b[j], weight = w[j];

			if (weight > capacity)
				storage[i][j] = knapsack_helper(capacity, items - 1, b, w);
			else
				storage[i][j] = std::max(knapsack_helper(capacity, items - 1, b, w),
											knapsack_helper(capacity - weight, items - 1, b, w) + benefit);
		}

		return storage[i][j];
	}
}

int knapsack(int capacity, int items, int b[], int w[]) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			storage[i][j] = UNKNOWN;

	return knapsack_helper(capacity, items, b, w);
}

void get_solution(int capacity, int items, int w[]) {
	if (items == 0) // items <= 0
		return; // Base case: no capacity or no items left
	else {
		int i = capacity - 1, j = items - 1;

		if (j == 0) {
			solution[j] = storage[i][j] != 0 ? 1 : 0;
		} else if (storage[i][j] == storage[i][j - 1]) {
			solution[j] = 0;
			get_solution(capacity, items - 1, w);
		} else {
			solution[j] = 1;
			get_solution(capacity - w[j], items - 1, w);
		}
	}
}

void print_storage() {
	// Header
	std::cout << " \t";
	for (int i = 0; i < n; i++)
		std::cout << i + 1 << '\t';
	std::cout << '\n';

	std::cout << " \t";
	for (int i = 0; i < n; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	// Print storage matrix
	for (int i = 0; i < m; i++) {
		std::cout << i + 1 << '\t';
		for (int j = 0; j < n; j++)
			std::cout << storage[i][j] << '\t';
		std::cout << '\n';
	}

	// Footer
	std::cout << " \t";
	for (int i = 0; i < n; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	std::cout << " \t";
	for (int i = 0; i < n; i++)
		std::cout << i + 1 << '\t';
	std::cout << '\n';
}


int main() {
	m = 20;
	int b[] = { 3, 2, 1, 4 };
	int w[] = { 7, 5, 6, 8 };
	n = sizeof(b) / sizeof(int);
	solution = new int[n];

	storage = new int*[m];

	for (int i = 0; i < m; i++)
		storage[i] = new int[n];

	knapsack(m, n, b, w);
	print_storage();
	get_solution(m, n, w);

	std::cout << "Solution: ( ";
	for (int i = 0; i < n; i++)
		std::cout << solution[i] << " ";
	std::cout << ")\n";

	delete[] solution;

	for (int i = 0; i < m; i++)
		delete[] storage[i];
	delete[] storage;

	return 0;
}
