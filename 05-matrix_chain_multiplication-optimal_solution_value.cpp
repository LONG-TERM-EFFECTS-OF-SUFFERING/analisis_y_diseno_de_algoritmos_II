#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>

int n;
std::vector <int> matrices;


int get_value(int i, int j) {
	if (i == j)
		return 0;
	else { // i < j
		int min = INT_MAX;

		for (int k = i; k < j; k++) {
			int value = get_value(i, k) + get_value(k + 1, j)
							+ matrices[i - 1] * matrices[k] * matrices[j];
			if (value < min)
				min = value;
		}

		return min;
	}
}


int main() {
	matrices = { 30, 35, 15, 5, 10, 20, 25 };
	n = matrices.size() == 2 ? 1 : matrices.size() - 1;

	int min_multiplications = get_value(1, n);
	std::cout << "Minimum number of multiplications is: " << min_multiplications << '\n';

	return 0;
}
