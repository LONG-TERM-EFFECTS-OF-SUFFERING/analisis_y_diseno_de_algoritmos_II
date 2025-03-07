#include <iostream>
#include <limits>

int best_count = std::numeric_limits <int>::max();
int* best_combination = nullptr;


void coin_change_exhaustive(int denominations[], int n, int index, int remaining, int count, int* current) {
	if (remaining == 0) {
		if (count < best_count) {
			best_count = count;
			for (int j = 0; j < n; j++)
				best_combination[j] = current[j];
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

		coin_change_exhaustive(denominations, n, index + 1, new_remaining, new_count, current);
	}

	current[index] = 0;
}

int* approach_2(int denominations[], int n, int amount) {
	best_combination = new int[n]();
	int* current = new int[n]();

	coin_change_exhaustive(denominations, n, 0, amount, 0, current);

	return best_combination;
}


int main() {
	int denominations[] = { 1, 5 };
	int amount = 6;
	int n = sizeof(denominations) / sizeof(int);
	int* result = approach_2(denominations, n, amount);

	for (int i = 0; i < n; i++)
		std::cout << result[i] << " ";
	std::cout << std::endl;

	delete[] result;

	return 0;
}
