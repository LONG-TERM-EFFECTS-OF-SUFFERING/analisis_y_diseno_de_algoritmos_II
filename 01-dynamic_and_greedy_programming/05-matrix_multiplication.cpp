#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int p, q, r;
std::vector <std::vector <int>> A, B;


std::vector <std::vector <int>> multiply_matrices() {
	std::vector <std::vector <int>> C = std::vector <std::vector <int>>(p, std::vector<int>(r));

	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++) {
			C[i][j] = 0;
				for (int k = 0; k < q; k++)
					C[i][j] += A[i][k] * B[k][j]; // p r q scalar multiplications
		}

	return C;
}


int main() {
	p = 4, q = 5, r = 6;

	A = std::vector <std::vector <int>>(p, std::vector<int>(q)); // p x q
	B = std::vector <std::vector <int>>(q, std::vector<int>(r)); // q x r

	std::srand(std::time(0));

	for (int i = 0; i < p; i++)
		for (int j = 0; j < q; j++)
			A[i][j] = std::rand() % 10;

	for (int i = 0; i < q; i++)
		for (int j = 0; j < r; j++)
			B[i][j] = std::rand() % 10;

	std::vector <std::vector <int>> C = multiply_matrices(); // p x r

	for (int i = 0; i < p; i++) {
		for (int j = 0; j < r; j++)
			std::cout << C[i][j] << " ";
		std::cout << std::endl;
	}

	return 0;
}
