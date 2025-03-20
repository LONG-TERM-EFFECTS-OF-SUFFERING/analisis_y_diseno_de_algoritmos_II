#include <algorithm>
#include <iostream>
#include <vector>


int get_value(int m, std::vector <int> b, std::vector <int> w, int j) {
	if (j == 0)
		return 0;
	else {
		int benefit = b[j - 1], weight = w[j - 1];

		if (weight > m)
			return get_value(m, b, w, j - 1);
		else
			return std::max(get_value(m, b, w, j - 1),
						get_value(m - weight, b, w, j - 1) + benefit);
	}
}


int main() {
	int m = 20;
	std::vector <int> b= { 3, 2, 1, 4 };
	std::vector <int> w = { 7, 5, 6, 8 };
	int n = b.size();

	if (m < 0) {
		std::cerr << "Error: capacity cannot be negative\n";
		return 1;
	}

	if (sizeof(b) != sizeof(w)) {
		std::cerr << "Error: benefits and weights vectors must be of the same size\n";
		return 1;
	}

	int max_benefit = get_value(m, b, w, n);
	std::cout << "The maximum benefit is: " << max_benefit << '\n';

	return 0;
}
