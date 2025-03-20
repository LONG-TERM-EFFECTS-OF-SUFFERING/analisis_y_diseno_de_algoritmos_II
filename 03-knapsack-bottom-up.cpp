#include <algorithm>
#include <iostream>
#include <vector>

int m, n;
std::vector <int> b, w, solution;
std::vector <std::vector <int>> storage;


void knapsack() {
	// Initialize the first column (item 0)
	for (int i = 0; i < m; i++)
		storage[i][0] = 0;

	// Initialize the second column (item 1)
	for (int i = 0; i < m; i++)
		if (i + 1 >= w[0]) // [1,m]
			storage[i][1] = b[0];
		else
			storage[i][1] = 0;

	// Left to right - up to bottom
	for (int i = 2; i < n + 1; i++) // Columns (items)
		for (int j = 0; j < m; j++) { // Rows (capacity)
			if (j + 1 < w[i - 1])
				storage[j][i] = storage[j][i - 1];
			else {
				int skip = storage[j][i - 1];
				int pick;
				int pick_index = j - w[i - 1];

				if (pick_index >= 0)
					pick = storage[pick_index][i - 1] + b[i - 1];
				else
					pick = b[i - 1];

				storage[j][i] = std::max(skip, pick);
			}
		}
}

void get_solution(int capacity, int items) {
	if (items == 0) // items <= 0
		return; // Base case: no items left
	else {
		if (storage[capacity - 1][items] == storage[capacity - 1][items - 1]) {
			solution[items - 1] = 0;
			get_solution(capacity, items - 1);
		} else {
			solution[items] = 1;
			get_solution(capacity - w[items - 1], items - 1);
		}
	}
}

void print_storage() {
	// Header
	std::cout << " \t";
	for (int i = 0; i < n + 1; i++)
		std::cout << i << '\t';
	std::cout << '\n';

	std::cout << " \t";
	for (int i = 0; i < n + 1; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	// Print storage matrix
	for (int i = 0; i < m; i++) {
		std::cout << i + 1 << '\t';
		for (int j = 0; j < n + 1; j++)
			std::cout << storage[i][j] << '\t';
		std::cout << '\n';
	}

	// Footer
	std::cout << " \t";
	for (int i = 0; i < n + 1; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	std::cout << " \t";
	for (int i = 0; i < n + 1; i++)
		std::cout << i << '\t';
	std::cout << '\n';
}


int main() {
	m = 20;
	b = { 3, 2, 1, 4 };
	w = { 7, 5, 6, 8 };
	n = b.size();

	if (m < 0) {
		std::cerr << "Error: capacity cannot be negative\n";
		return 1;
	}

	if (n != w.size()) {
		std::cerr << "Error: benefits and weights vectors must be of the same size\n";
		return 1;
	}

	solution = std::vector <int>(n, 0);
	storage = std::vector <std::vector <int>>(m, std::vector <int>(n + 1, 0));

	knapsack();
	print_storage();
	get_solution(m, n);

	std::cout << "Solution: ( ";
	for (const auto &election : solution)
		std::cout << election << ' ';
	std::cout << ")\n";

	return 0;
}
