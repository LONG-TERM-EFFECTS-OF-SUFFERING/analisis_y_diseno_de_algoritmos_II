#include <algorithm>
#include <iostream>


int get_value(std::string x, std::string y) {
	int x_length = x.length(), y_length = y.length();

	if (x_length == 0 || y_length == 0)
		return 0;
	else {
		int i = x_length - 1, j = y_length - 1;
		std::string x_substr = x.substr(0, i), y_substr = y.substr(0, j);

		if (x[i] == y[j])
			return get_value(x_substr, y_substr) + 1;
		else
			return std::max(get_value(x_substr, y), get_value(x, y_substr));
	}
}


int main() {
	std::string x = "BDCABA";
	std::string y = "ABCBDA";

	int max_benefit = get_value(x, y);
	std::cout << "The maximum benefit is: " << max_benefit << '\n';

	return 0;
}
