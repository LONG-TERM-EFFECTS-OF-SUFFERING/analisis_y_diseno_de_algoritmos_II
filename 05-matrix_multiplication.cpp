#include <iostream>
#include <cstdlib>
#include <ctime>


int** multiply_matrices(int** A, int** B, int p, int q, int r) {
	int** C = new int*[p];

	for (int i = 0; i < p; i++)
		C[i] = new int[r];

	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++) {
			C[i][j] = 0;
				for (int k = 0; k < q; k++)
					C[i][j] += A[i][k] * B[k][j]; // p r q scalar multiplications
		}

	return C;
}

int main() {
	int p = 4, q = 5, r = 6;

	int** A = new int*[p]; // p x q

	for (int i = 0; i < p; i++)
		A[i] = new int[q];

	int** B = new int*[q]; // q x r

	for (int i = 0; i < q; i++)
		B[i] = new int[r];

	std::srand(std::time(0));

	for (int i = 0; i < p; i++)
		for (int j = 0; j < q; j++)
			A[i][j] = std::rand() % 10;

	for (int i = 0; i < q; i++)
		for (int j = 0; j < r; j++)
			B[i][j] = std::rand() % 10;

	int** C = multiply_matrices(A, B, p, q, r); // p x r

	for (int i = 0; i < p; i++) {
		for (int j = 0; j < r; j++)
			std::cout << C[i][j] << " ";
		std::cout << std::endl;
	}

	for (int i = 0; i < p; i++) {
		delete[] A[i];
		delete[] C[i];
	}
	delete[] A;
	delete[] C;

	for (int i = 0; i < q; i++)
		delete[] B[i];
	delete[] B;

	return 0;
}
