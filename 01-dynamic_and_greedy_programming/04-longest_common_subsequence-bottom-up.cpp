#include <algorithm>
#include <iostream>
#include <vector>

int n, m;
std::string x, y;
std::vector <std::vector <int>> storage;
std::vector <std::vector <char>> B;


int LCS(int i, int j) {
	// Initialize the first row and column
	for (int i = 0; i < m + 1; i++) {
		storage[0][i] = 0;
		B[0][i] = 'N';
	}

	for (int i = 0; i < n + 1; i++) {
		storage[i][0] = 0;
		B[i][0] = 'N';
	}

	// Left to right - up to bottom
	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < m + 1; j++) {
			char x_letter = x[i - 1], y_letter = y[j - 1];

			if (x_letter == y_letter) {
				storage[i][j] = storage[i - 1][j - 1] + 1;
				B[i][j] = '\\';
			} else
				if (storage[i - 1][j] >= storage[i][j - 1]) {
					storage[i][j] = storage[i - 1][j];
					B[i][j] = '|';
				} else {
					storage[i][j] = storage[i][j - 1];
					B[i][j] = '-';
				}
		}

	return storage[i][j];
}

std::string get_solution(int i, int j) {
	if (i == 0 || j == 0)
		return "";
	else if (B[i][j] == '\\')
		return get_solution(i - 1, j - 1) + x[i - 1];
	else if (B[i][j] == '|')
		return get_solution(i - 1, j);
	else // B[i][j] == '-'
		return get_solution(i, j - 1);
}

void print_storage() {
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
	for (int i = 0; i <= n; i++) {
		std::cout << (i == 0 ? ' ': x[i - 1]) << '\t';
		for (int j = 0; j <= m; j++)
			std::cout << storage[i][j] << B[i][j] << '\t';
		std::cout << '\n';
	}
}


int main() {
	x = "ABCBDAB";
	y = "BDCABA";

	n = x.length();
	m = y.length();

	storage = std::vector <std::vector <int>>(n + 1, std::vector <int>(m + 1));
	B = std::vector <std::vector <char>>(n + 1, std::vector <char>(m + 1));

	int solution_length = LCS(n, m);
	print_storage();
	std::string solution = get_solution(n, m);
	std::cout << "LCS(" << x << ',' << y << "): " << solution << " with length " << solution_length << '\n';

	return 0;
}
