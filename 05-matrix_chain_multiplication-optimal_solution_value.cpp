#include <algorithm>
#include <iostream>
#include <limits.h>


int get_value(int matrices[], int i, int j) {
	if (i == j)
		return 0;
	else { // i < j
		int min = INT_MAX;

		for (int k = i; k < j; k++) {
			int value = get_value(matrices, i, k) + get_value(matrices, k + 1, j)
							+ matrices[i - 1] * matrices[k] * matrices[j];
			if (value < min)
				min = value;
		}

		return min;
	}
}


int main() {
	int matrices[] = { 10, 100, 5, 50 };
	int array_n = sizeof(matrices) / sizeof(int);
	int n;

	if (array_n == 2)
		n = 1;
	else
		n = array_n - 1;

	int min_multiplications = get_value(matrices, 1, n);
	std::cout << "Minimum number of multiplications is: " << min_multiplications << '\n';

	return 0;
}
