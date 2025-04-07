#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>

#define UNKNOWN -1 // Contents denote an empty cell

int n;
std::vector <int> matrices;
std::vector <std::vector <int>> multiplications_matrix, k_matrix;


int MCM(int i_, int j_) {
	// First diagonal
	for (int i = 0; i < n; i++) {
		multiplications_matrix[i][i] = 0;
		k_matrix[i][i] = 0;
	}

	// Travel along the diagonals
	for (int l = 2; l <= n; l++) // Subchain length
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;

			int zero_indexed_i = i - 1;
			int zero_indexed_j = j - 1;

			multiplications_matrix[zero_indexed_i][zero_indexed_j] = INT_MAX;

			for (int k = i; k < j; k++) {
				int value = multiplications_matrix[zero_indexed_i][k - 1] + multiplications_matrix[k][zero_indexed_j]
								+ matrices[i - 1] * matrices[k] * matrices[j];
				if (value < multiplications_matrix[zero_indexed_i][zero_indexed_j]) {
					multiplications_matrix[zero_indexed_i][zero_indexed_j] = value;
					k_matrix[zero_indexed_i][zero_indexed_j] = k;
				}
			}
		}

	return multiplications_matrix[i_ - 1][j_ - 1];
}

std::string get_solution(int i, int j) {
	if (i == j)
		return "A_" + std::to_string(i);
	else {
		std::string left = get_solution(i, k_matrix[i - 1][j - 1]);
		std::string right = get_solution(k_matrix[i - 1][j - 1] + 1, j);

		return '(' + left + ' ' + right + ')';
	}
}

void print_storage(std::vector <std::vector <int>> matrix) {
	// Header
	std::cout << " \t";
	for (int i = 0; i < n; i++)
		std::cout << (i + 1) << '\t';
	std::cout << '\n';

	std::cout << " \t";
	for (int i = 0; i < n; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	// Print storage matrix
	for (int i = 0; i < n; i++) {
		std::cout << (i + 1) << '\t';
		for (int j = 0; j < n; j++) {
			if (j >= i)
				std::cout << matrix[i][j] << '\t';
			else
				std::cout << 'x' << '\t';
		}
		std::cout << '\n';
	}
}


int main() {
	matrices = { 30, 35, 15, 5, 10, 20, 25 };
	n = matrices.size() == 2 ? 1 : matrices.size() - 1;

	multiplications_matrix = std::vector <std::vector <int>>(n, std::vector <int>(n));
	k_matrix = std::vector <std::vector <int>>(n, std::vector <int>(n));

	MCM(1, n);
	// print_storage(multiplications_matrix);
	std::cout << '\n';
	// print_storage(k_matrix);
	std::cout << "\nOptimal parenthesization: " << get_solution(1, n) << std::endl;

	return 0;
}
