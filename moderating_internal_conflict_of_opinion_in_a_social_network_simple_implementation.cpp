#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>


struct AgentGroup {
	int n; // Number of agents
	int o_1; // Opinion on statement 1
	int o_2; // Opinion on statement 2
	double r; // Rigidity level

	AgentGroup(int n, int o_1, int o_2, double r) :
		n(n), o_1(o_1), o_2(o_2), r(r) { }

};

std::ostream& operator<<(std::ostream& os, const AgentGroup& group) {
	os << "n=" << group.n << ", o_1=" << group.o_1 << ", o_2=" << group.o_2 << ", r=" << group.r;
	return os;
}

struct SocialNetwork {
	std::vector <AgentGroup> groups;
	int R_max; // Maximum effort available

	SocialNetwork(int R_max) : R_max(R_max) { }

	void add_group(const AgentGroup &group) {
		groups.push_back(group);
	}
};

double calculate_IC(const SocialNetwork &socialNetwork);

std::ostream& operator<<(std::ostream& os, const SocialNetwork& network) {
	os << "IC=" << calculate_IC(network)
		<< "\nR_max=" << network.R_max
		<< "\nGroups:\n";
	for (const auto &group : network.groups)
		os << group << '\n';
	return os;
}

/* -------------------------------------------------------------------------- */

double calculate_IC(const SocialNetwork &socialNetwork) {
	double numerator = 0.0;
	int denominator = 0;

	for (const auto &group : socialNetwork.groups) {
		int n = group.n;
		int o_1 = group.o_1;
		int o_2 = group.o_2;

		numerator += n * std::pow(o_1 - o_2, 2);
		denominator += n;
	}

	return numerator / denominator;
}

int calculate_effort(const SocialNetwork &social_network, const std::vector<int> &strategy) {
	if (strategy.size() != social_network.groups.size())
		throw std::invalid_argument("Error: strategy length must equal the number of agent groups");

	int effort = 0;

	for (size_t i = 0; i < social_network.groups.size(); ++i) {
		const auto &group = social_network.groups[i];
		int e_i = strategy[i];

		if (e_i > 0)
			effort += std::ceil(
				std::abs(group.o_1 - group.o_2) * group.r * e_i
			);
	}

	return effort;
}

SocialNetwork apply_strategy(const SocialNetwork &social_network, const std::vector<int> &strategy) {
	if (strategy.size() != social_network.groups.size())
		throw std::invalid_argument("Error: strategy length must equal the number of agent groups");

	SocialNetwork modified_network(social_network.R_max);

	for (size_t i = 0; i < social_network.groups.size(); ++i) {
		const auto &group = social_network.groups[i];
		int n = group.n;
		int e = strategy[i];

		if (e > n)
			throw std::invalid_argument("Error: strategy value cannot exceed the number of agents in the group");

		// Only include groups that still have agents after applying the strategy
		if (e < n) {
			modified_network.add_group(AgentGroup(
				n - e,
				group.o_1,
				group.o_2,
				group.r
			));
		}
	}

	return modified_network;
}

/* -------------------------------------------------------------------------- */

int n, R_max;
std::vector <std::vector <double>> storage;
std::vector <std::vector <int>> decisions;

std::vector <int> IC(const SocialNetwork &social_network) {
	int R_max = social_network.R_max;
	const std::vector <AgentGroup> &groups = social_network.groups;

	// Base case: no groups, no conflict
	for (int r = 0; r <= R_max; r++)
		storage[0][r] = 0;

	// Bottom-up
	for (int i = 1; i <= n; i++) {
		const auto &group = groups[i - 1];
		int n_i = group.n, o_1 = group.o_1, o_2 = group.o_2, r_i = group.r;

		double conflict_per_agent = std::pow(o_1 - o_2, 2);
		double effort_per_agent = std::abs(o_1 - o_2) * r_i;

		for (int r = 0; r <= R_max; r++) {
			storage[i][r] = std::numeric_limits <double>::infinity();

			// Try affecting k agents from current group
			for (int k = 0; k <= n_i; k++) {
				int required_effort = std::ceil(effort_per_agent * k);

				if (required_effort <= r) {
					// Calculate remaining conflict after affecting k agents
					double remaining_conflict = std::ceil((n_i - k) * conflict_per_agent);

					// Total conflict = optimal conflict for previous groups + remaining conflict
					double total_conflict = storage[i - 1][r - required_effort] + remaining_conflict;

					if (total_conflict < storage[i][r]) {
						storage[i][r] = total_conflict;
						decisions[i][r] = k;
					}
				}
			}
		}
	}

	std::vector <int> optimal_strategy(n, 0);
	int remaining_effort = R_max;

	for (int i = n; i > 0; i--) {
		int k = decisions[i][remaining_effort];
		optimal_strategy[i - 1] = k;

		const auto &group = groups[i - 1];
		double effort_per_agent = std::abs(group.o_1 - group.o_2) * group.r;
		int required_effort = std::ceil(k * effort_per_agent);

		remaining_effort -= required_effort;
	}

	return optimal_strategy;
}

void print_storage() {
	// Header
	std::cout << " \t";
	for (int i = 0; i <= R_max; i++)
		std::cout << i << '\t';
	std::cout << '\n';

	std::cout << " \t";
	for (int i = 0; i <= R_max; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	// Print storage matrix
	for (int i = 0; i <= n; i++) {
		std::cout << i << '\t';
		for (int j = 0; j <= R_max; j++)
			std::cout << storage[i][j] << '\t';
		std::cout << '\n';
	}

	// Footer
	std::cout << " \t";
	for (int i = 0; i <= R_max; i++)
		std::cout << '-' << '\t';
	std::cout << '\n';

	std::cout << " \t";
	for (int i = 0; i <= R_max; i++)
		std::cout << i << '\t';
	std::cout << '\n';
}


int main() {
	// Create a social network with maximum effort of 100
	R_max = 100;
	SocialNetwork network(R_max);

	// Add several agent groups with different properties
	network.add_group(AgentGroup(20, 50, 30, 0.8));
	network.add_group(AgentGroup(15, -50, 50, 1));
	network.add_group(AgentGroup(30, 80, 50, 0.5));
	network.add_group(AgentGroup(10, -100, 100, 0.9));

	n = network.groups.size();

	storage = std::vector <std::vector <double>>(n + 1, std::vector <double>(R_max + 1));
	decisions = std::vector <std::vector <int>>(n + 1, std::vector<int>(R_max + 1, 0));

	std::cout << network << '\n';

	std::vector <int> optimal_strategy = IC(network);
	std::cout << "Optimal strategy: ";
	for (int i = 0; i < optimal_strategy.size(); ++i)
		std::cout << optimal_strategy[i] << ' ';
	std::cout << '\n';

	SocialNetwork optimal_network = apply_strategy(network, optimal_strategy);
	std::cout << optimal_network << '\n';

	return 0;
}
