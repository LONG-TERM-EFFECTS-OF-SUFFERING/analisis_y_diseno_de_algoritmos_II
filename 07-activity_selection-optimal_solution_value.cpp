#include <iostream>
#include <string>


int get_solution_value(int s[], int f[], int i, int j) {
	if (j <= i + 1) {
		return 0;
	} else {
		int max = 0;

		for (int k = i + 1; k < j; k++) {
			if (s[k] >= f[i] && f[k] <= s[j]) { // a_k in S_(ij)
				int value = get_solution_value(s, f, i, k)
								+ get_solution_value(s, f, k, j) + 1;

				if (value > max)
					max = value;
			}
		}

		return max;
	}
}


int main() {
	int s[] = {
		3, // Dummy s_1
		1,
		2,
		6,
		8,
		5,
		10 // Dummy s_2
	};

	int f[] = {
		3, // Dummy f_1
		3,
		5,
		8,
		9,
		10,
		10, // Dummy f_2
	};

	int n = sizeof(s) / sizeof(int);

	std::cout << "Activities: ";
	for (int i = 0; i < n; i++)
		std::cout << '(' << s[i] << ','
			<< f[i] << ") ";
	std::cout << '\n';

	std::cout << "Selected activities: " + std::to_string(get_solution_value(s, f, 0, n)) << std::endl;

	return 0;
}
