#include <iostream>
#include <vector>
#include <limits>

int best_count = INT_MAX;
std::vector <int> best_combination;
std::vector <int> denominations;
int n, amount;


void coin_change_exhaustive(int index, int remaining, int count, std::vector <int> &current) {
	if (remaining == 0) {
		if (count < best_count) {

			best_count = count;
			best_combination = current;
		} else
			return;
	}

	if (index >= n || count >= best_count)
		return;

	int coin_value = denominations[index];
	int max_coins = remaining / coin_value;

	for (int i = max_coins; i >= 0; i--) {
		current[index] = i;
		int new_remaining = remaining - coin_value * i;
		int new_count = count + i;

		coin_change_exhaustive(index + 1, new_remaining, new_count, current);
	}

	current[index] = 0;
}

void approach_2() {
	std::vector <int> current(n, 0);

	coin_change_exhaustive(0, amount, 0, current);
}


int main() {
	denominations = { 1, 5, 10, 2 };
	amount = 30;
	n = denominations.size();

	approach_2();

	for (const auto &coins : best_combination)
		std::cout << coins << ' ';
	std::cout << '\n';

	return 0;
}
