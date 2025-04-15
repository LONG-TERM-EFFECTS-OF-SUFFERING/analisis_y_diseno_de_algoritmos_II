/*
	A company needs to mix two types of cattle feed (x and y) to meet nutritional requirements:

	- Each portion must contain:
		- At least 60 grams of protein.
		- At least 30 grams of fat.

	Feed specifications:
		- Package X costs $80 and contains:
			- 15 grams of protein.
			- 10 grams of fat.

		- Package Y costs $50 and contains:
			- 20 grams of protein.
			- 5 grams of fat.

	Variables:
		x: number of packages of feed x to use.
		y: number of packages of feed y to use.

	Objective: minimize total cost while meeting nutritional constraints.
*/
var float: x;
var float: y;
var float: c;

constraint 15 * x + 20 * y >= 60;
constraint 10 * x + 5 * y >= 30;

constraint x >= 0;
constraint y >= 0;

constraint c = 80 * x + 50 * y;
solve minimize c;

output ["x = ", show(x), "\ny = ", show(y), "\nc = ", show(c)]
