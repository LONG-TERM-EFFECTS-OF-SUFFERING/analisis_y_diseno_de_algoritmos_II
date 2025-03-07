#include <algorithm>
#include <iostream>
#include <limits.h>

#define UNKNOWN -1 // Contents denote an empty cell
int n;
int** multiplications_matrix;
int** k_matrix;


int MCM_helper(int matrices[], int i, int j) {
	if (multiplications_matrix[i - 1][j - 1] == UNKNOWN) {
		int min = INT_MAX;

		for (int k = i; k < j; k++) {
			int value = MCM_helper(matrices, i, k) + MCM_helper(matrices, k + 1, j)
							+ matrices[i - 1] * matrices[k] * matrices[j];
			if (value < min) {
				min = value;
				k_matrix[i - 1][j - 1] = k;
			}
		}

		multiplications_matrix[i - 1][j - 1] = min;
	}

	return multiplications_matrix[i - 1][j - 1];
}

int MCM(int matrices[], int i, int j) {
	for (int i = 0; i < n; i++) {
		multiplications_matrix[i][i] = 0;
		k_matrix[i][i] = 0;
	}

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			multiplications_matrix[i][j] = UNKNOWN;
			k_matrix[i][j] = UNKNOWN;
		}

	return MCM_helper(matrices, i, j);
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

void print_storage(int** matrix, int n) {
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
	int matrices[] = { 30, 35, 15, 5, 10, 20, 25 };
	int array_n = sizeof(matrices) / sizeof(int);

	if (array_n == 2)
		n = 1;
	else
		n = array_n - 1;

	multiplications_matrix = new int*[n];
	k_matrix = new int*[n];

	for (int i = 0; i < n; i++) {
		multiplications_matrix[i] = new int[n];
		k_matrix[i] = new int[n];
	}

	MCM(matrices, 1, n);
	print_storage(multiplications_matrix, n);
	std::cout << '\n';
	print_storage(k_matrix, n);
	std::cout << "\nOptimal parenthesization: " << get_solution(1, n) << std::endl;

	for (int i = 0; i < n; i++) {
		delete[] multiplications_matrix[i];
		delete[] k_matrix[i];
	}
	delete[] multiplications_matrix;
	delete[] k_matrix;

	return 0;
}
