#include <iostream>
#include <vector>

std::vector <int> denominations;
int amount;


std::vector <int> approach_1() {
	int n = denominations.size();
	std::vector <int> solution(n, 0);

	for (int i = n - 1; i >= 0; i--) {
		solution[i] = amount / denominations[i];
		amount -= solution[i] * denominations[i];
	}

	return solution;
}


int main() {
	denominations = { 1, 5, 10, 25 };
	amount = 30;


	std::vector <int> result = approach_1();

	for (const auto &coins : result)
		std::cout << coins << ' ';
	std::cout << '\n';

	return 0;
}
