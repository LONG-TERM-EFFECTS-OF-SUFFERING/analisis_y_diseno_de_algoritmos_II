#include <algorithm>
#include <iostream>
#include <vector>

#define UNKNOWN -1

int m, n;
std::vector <int> b, w, solution;
std::vector <std::vector <int>> storage;


int knapsack_helper(int capacity, int items) {
	if (items == 0) // items <= 0
		return 0; // Base case: no items left
	else {
		int i = capacity - 1;
		if (storage[i][items] == UNKNOWN) {
			int benefit = b[items - 1], weight = w[items - 1];

			if (weight > capacity)
				storage[i][items] = knapsack_helper(capacity, items - 1);
			else
				storage[i][items] = std::max(knapsack_helper(capacity, items - 1),
											knapsack_helper(capacity - weight, items - 1) + benefit);
		}

		return storage[i][items];
	}
}

int knapsack(int capacity, int items) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n + 1; j++)
			storage[i][j] = UNKNOWN;

	return knapsack_helper(capacity, items);
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
	for (int i = 0; i <= n; i++)
		std::cout << i << '\t';
	std::cout << '\n';

	std::cout << " \t";
	for (int i = 0; i <= n; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	// Print storage matrix
	for (int i = 0; i < m; i++) {
		std::cout << i + 1 << '\t';
		for (int j = 0; j <= n; j++)
			std::cout << storage[i][j] << '\t';
		std::cout << '\n';
	}

	// Footer
	std::cout << " \t";
	for (int i = 0; i <= n; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	std::cout << " \t";
	for (int i = 0; i <= n; i++)
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

	if (n != (int) w.size()) {
		std::cerr << "Error: benefits and weights vectors must be of the same size\n";
		return 1;
	}

	solution = std::vector <int>(n, 0);
	storage = std::vector <std::vector <int>>(m, std::vector <int>(n + 1, 0));

	knapsack(m, n);
	print_storage();
	get_solution(m, n);

	std::cout << "Solution: ( ";
	for (const auto &election : solution)
		std::cout << election << ' ';
	std::cout << ")\n";

	return 0;
}
