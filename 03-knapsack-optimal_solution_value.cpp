#include <algorithm>
#include <iostream>


int get_value(int m, int benefits[], int weights[], int j) {
	if (j == 0)
		return 0;
	else {
		int benefit = benefits[j - 1], weight = weights[j - 1];

		if (weight > m)
			return get_value(m, benefits, weights, j - 1);
		else
			return std::max(get_value(m, benefits, weights, j - 1),
						get_value(m - weight, benefits, weights, j - 1) + benefit);
	}
}


int main() {
	int m = 20;
	int b[] = { 3, 2, 1, 4 };
	int w[] = { 7, 5, 6, 8 };

	if (m < 0) {
		std::cerr << "Error: capacity cannot be negative\n";
		return 1;
	}

	if (sizeof(b) != sizeof(w)) {
		std::cerr << "Error: benefits and weights arrays must be of the same size\n";
		return 1;
	}

	int n = sizeof(b) / sizeof(int);

	int max_benefit = get_value(m, b, w, n);
	std::cout << "The maximum benefit is: " << max_benefit << '\n';

	return 0;
}
