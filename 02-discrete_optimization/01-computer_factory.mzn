/*
	A company manufactures desktop and notebook computers and wants to determine
	the optimal production quantity to maximize profits:

	- Each computer (desktop or notebook) requires 1 processing chip.
	Available: 10,000 processing chips.

	- Each computer requires memory (16MB per chip):
	- Notebook: 1 chip (16MB)
	- Desktop: 2 chips (32MB)
	Available memory chips: 15,000.

	- Assembly time required:
	- Notebook: 4 minutes
	- Desktop: 3 minutes
	Total available assembly time: 25,000 minutes.

	- Profit per unit:
	- Notebook: $750
	- Desktop: $1000

	Variables:
	x_1: number of notebooks to produce
	x_2: number of desktops to produce
*/
var int: x_1;
var int: x_2;

constraint x_1 + x_2 <= 10000;
constraint x_1 + 2 * x_2 <= 15000;
constraint 4 * x_1 + 3 * x_2 <= 25000;

constraint x_1 >= 0;
constraint x_2 >= 0;

solve maximize 750 * x_1 + 1000 * x_2;

output ["x_1 = ", show(x_1), "\nx_2 = ", show(x_2)]
