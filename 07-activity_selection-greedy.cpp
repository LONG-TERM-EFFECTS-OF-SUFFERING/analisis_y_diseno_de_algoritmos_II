#include <iostream>
#include <string>


std::string activity_selector(int* solution, int n, int s[], int f[], int k) {
	int m = k + 1;

	while (m < n && s[m] < f[k])
		m = m + 1;

	if (m < n) {
		solution[m] = 1;
		return "(" + std::to_string(s[m]) + "," + std::to_string(f[m]) + ") " + activity_selector(solution, n, s, f, m);
	} else // m >= n
		return "";
}


int main() {
	int s[] = {
		3, // Dummy s_1
		1,
		2,
		6,
		8,
		5
	};

	int f[] = {
		3, // Dummy f_1
		3,
		5,
		8,
		9,
		10
	};

	int n = sizeof(s) / sizeof(int);
	int* solution = new int[n];

	std::cout << "Activities: ";
	for (int i = 0; i < n; i++)
		std::cout << '(' << s[i] << ','
			<< f[i] << ") ";
	std::cout << '\n';
	std::cout << "Selected activities: " + activity_selector(solution, n, s, f, 0);
	// for (int i = 0; i < n; i++)
	// 	if (solution[i] == 1) {
	// 		std::cout << '(' << s[i] << ','
	// 			<< f[i] << ") ";
	// 	}

	std::cout << std::endl;

	delete[] solution;

	return 0;
}