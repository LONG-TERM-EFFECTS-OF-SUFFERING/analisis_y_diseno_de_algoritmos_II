import numpy as np
from numpy.typing import NDArray
from tabulate import tabulate


z = np.array([1, -3, -2, 0, 0, 0, 0], dtype=np.float64)
x = np.array([
	[0, 1, 2, 1, 0, 0, 0],
	[0, 2, 1, 0, 1, 0, 0],
	[0, -1, 1, 0, 0, 1, 0],
	[0, 0, 1, 0, 0, 0, 1]
], dtype=np.float64)
b = np.array([0, 6, 8, 1, 2], dtype=np.float64)

n_original_vars = 2
n = len(x[0])
column_labels = [f"x_{i + 1}" for i in range(n - 1)]
column_labels = ["z"] + column_labels
row_labels = [f"x_{n_original_vars + (i + 1)}" for i in range(n - n_original_vars - 1)]
row_labels = ["", "z"] + row_labels

def create_table(z: NDArray[np.float64], x: NDArray[np.float64], b: NDArray[np.float64]):
	table = np.vstack([column_labels, z, x])
	rhs = ["RHS"] + list(b)
	table = np.column_stack([row_labels, table, rhs])
	return table

def select_input_var(z: NDArray[np.float64]) -> tuple[int, int]:
	return np.min(z), np.argmin(z)

def get_pivot_row(x, b: NDArray[np.float64], input_var_column):
	theta_values = []

	for i in range(len(b) - 1):
		denominator = x[i, input_var_column]
		if denominator == 0:
			theta_values.append(np.inf)
		else:
			theta_values.append(b[i + 1] / denominator)

	theta_values = [theta if theta > 0 else np.inf for theta in theta_values]

	return np.argmin(theta_values)

def feasible_solution(b: NDArray[np.float64]) -> bool:
	return np.all(b >= 0)

if not feasible_solution(b):
	raise ValueError("Error: initial solution is not feasible")

# Input var selection
input_var_value, input_var_column = select_input_var(z)

while input_var_value < 0:
	# Outgoing variable and pivoting
	pivot_row = get_pivot_row(x, b, input_var_column)
	pivot = x[pivot_row, input_var_column]

	row_labels[pivot_row + 2] = column_labels[input_var_column]

	# Get 1 in the intersection
	x[pivot_row] = x[pivot_row] / pivot
	b[pivot_row + 1] = b[pivot_row + 1] / pivot

	# Update equations
	factor = z[input_var_column]
	z = z - (x[pivot_row] * factor)
	b[0] = b[0] - (b[pivot_row + 1] * factor)

	for i in range(len(x)):
		if i == pivot_row:
			continue
		factor = x[i, input_var_column]
		x[i] = x[i] - (x[pivot_row] * factor)
		b[i + 1] = b[i + 1] - (b[pivot_row + 1] * factor)

	input_var_value, input_var_column = select_input_var(z)

print("Final tableau:")
print(tabulate(create_table(z, x, b), tablefmt="grid", floatfmt=".2f"))
print("\nOptimal value (z):", b[0])
print("Solution (variables):", b[1:])
