#include <iostream>
#include <vector>
#include <string>

int n;
std::vector <int> s, f;


int get_solution_value(std::vector <int> &s, std::vector <int> &f, int i, int j) {
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

int get_solution_value_helper() {
	std::vector <int> new_s = s, new_f = f;
	new_s.insert(new_s.begin(), INT_MIN);
	new_f.insert(new_f.begin(), INT_MIN);
	new_s.insert(new_s.end(), INT_MAX);
	new_f.insert(new_f.end(), INT_MAX);

	return get_solution_value(new_s, new_f, 0, n + 1);
}


int main() {
	s = { 1, 2, 6, 8, 5 };
	f = { 3, 5, 8, 9, 10 };

	n = s.size();

	std::cout << "Activities: ";
	for (int i = 0; i < n; i++)
		std::cout << '(' << s[i] << ','
			<< f[i] << ") ";
	std::cout << '\n';

	std::cout << "Number of selected activities: " + std::to_string(get_solution_value_helper()) << std::endl;

	return 0;
}
