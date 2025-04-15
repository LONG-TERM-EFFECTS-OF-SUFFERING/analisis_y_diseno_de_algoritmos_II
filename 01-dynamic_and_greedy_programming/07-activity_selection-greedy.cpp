#include <iostream>
#include <vector>
#include <string>

int n;
std::vector <int> s, f;
std::vector <int> solution;


std::string activity_selector(std::vector <int> s, std::vector <int> f, int k) {
	int m = k + 1;

	while (m < n && s[m] < f[k])
		m = m + 1;

	if (m < n) {
		solution[m] = 1;
		return "(" + std::to_string(s[m]) + "," + std::to_string(f[m]) + ") " + activity_selector(s, f, m);
	} else // m >= n
		return "";
}

std::string activity_selector_helper() {
	std::vector <int> new_s = s, new_f = f;
	new_s.insert(new_s.begin(), INT_MIN);
	new_f.insert(new_f.begin(), INT_MIN);

	return activity_selector(new_s, new_f, 0);
}


int main() {
	s = { 1, 2, 6, 8, 5 };
	f = { 3, 5, 8, 9, 10 };

	n = s.size();
	solution = std::vector <int>(n);

	std::cout << "Activities: ";
	for (int i = 0; i < n; i++)
		std::cout << '(' << s[i] << ','
			<< f[i] << ") ";
	std::cout << '\n';
	std::cout << "Selected activities: " + activity_selector_helper();

	return 0;
}
