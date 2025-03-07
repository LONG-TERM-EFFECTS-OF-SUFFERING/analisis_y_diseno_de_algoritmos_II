#include <algorithm>
#include <iostream>

int m, n;
int** storage;
int* solution;


int knapsack(int capacity, int items, int b[], int w[]) {
	// Initialize the first column (item 0)
	for (int i = 0; i < m; i++)
		if (i + 1 >= w[0]) // [1,m]
			storage[i][0] = b[0];
		else
			storage[i][0] = 0;

	// Left to right - up to bottom
	for (int i = 1; i < n; i++) // Columns
		for (int j = 0; j < m; j++) { // Rows
			if (j + 1 < w[i])
				storage[j][i] = storage[j][i - 1];
			else {
				int skip = storage[j][i - 1];
				int pick;
				int pick_index = j - w[i];

				if (pick_index >= 0)
					pick = storage[pick_index][i - 1] + b[i];
				else
					pick = b[i];

				storage[j][i] = std::max(skip, pick);
			}
		}

	return storage[capacity - 1][items - 1];
}

void get_solution(int capacity, int items, int w[]) {
	if (items == 0) // items <= 0
		return; // Base case: no items left
	else {
		int i = capacity - 1, j = items - 1;

		if (j == 0)
			solution[j] = storage[i][j] != 0 ? 1 : 0;
		else if (storage[i][j] == storage[i][j - 1]) {
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
