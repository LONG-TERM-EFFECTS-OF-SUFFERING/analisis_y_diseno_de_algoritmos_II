#include <algorithm>
#include <iostream>

#define UNKNOWN -1 // Contents denote an empty cell
int n, m;
int** storage;
char** B;


int LCS_helper(std::string x, std::string y, int i, int j) {
	if (storage[i][j] == UNKNOWN) {
		if (x[i - 1] == y[j - 1]) {
			storage[i][j] = LCS_helper(x, y, i - 1, j - 1) + 1;
			B[i][j] = '\\';
		} else {
			int option_1 = LCS_helper(x, y, i - 1, j);
			int option_2 = LCS_helper(x, y, i, j - 1);

			if (option_1 >= option_2) {
				storage[i][j] = option_1;
				B[i][j] = '|';
			} else {
				storage[i][j] = option_2;
				B[i][j] = '-';
			}
		}
	}

	return storage[i][j];
}

int LCS(std::string x, std::string y) {
	// Initialize the first row and column
	for (int i = 0; i < m + 1; i++) {
		storage[0][i] = 0;
		B[0][i] = 'N';
	}

	for (int i = 0; i < n + 1; i++) {
		storage[i][0] = 0;
		B[i][0] = 'N';
	}

	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < m + 1; j++)
			storage[i][j] = UNKNOWN;

	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < m + 1; j++)
			B[i][j] = '?';


	return LCS_helper(x, y, n, m);
}

std::string get_solution(std::string x, int i, int j) {
	if (i == 0 || j == 0)
		return "";
	else if (B[i][j] == '\\')
		return get_solution(x, i - 1, j - 1) + x[i - 1];
	else if (B[i][j] == '|')
		return get_solution(x, i - 1, j);
	else // B[i][j] == '-'
		return get_solution(x, i, j - 1);
}

void print_storage(std::string x, std::string y) {
	// Header
	std::cout << " \t\t";
	for (int i = 0; i < m; i++)
		std::cout << y[i] << '\t';
	std::cout << '\n';

	std::cout << " \t\t";
	for (int i = 0; i < m; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	// Print storage matrix
	for (int i = 0; i < n + 1; i++) {
		std::cout << (i == 0 ? ' ': x[i - 1]) << '\t';
		for (int j = 0; j < m + 1; j++)
			std::cout << storage[i][j] << B[i][j] << '\t';
		std::cout << '\n';
	}
}


int main() {
	std::string x = "ABCBDAB";
	std::string y = "BDCABA";

	n = x.length();
	m = y.length();

	storage = new int*[n + 1];
	B = new char*[n + 1];

	for (int i = 0; i < n + 1; i++) {
		storage[i] = new int[m + 1];
		B[i] = new char[m + 1];
	}

	int solution_length = LCS(x, y);
	print_storage(x, y);
	std::string solution = get_solution(x, n, m);
	std::cout << "LCS(" << x << ',' << y << "): " << solution << '\n';

	for (int i = 0; i < n + 1; i++) {
		delete[] storage[i];
		delete[] B[i];
	}
	delete[] storage;
	delete[] B;

	return 0;
}
