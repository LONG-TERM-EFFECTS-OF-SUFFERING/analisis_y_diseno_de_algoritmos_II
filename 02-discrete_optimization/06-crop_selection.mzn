/*
	A vegetable farmer needs to allocate 200 acres among tomatoes, green peppers, and cucumbers,
	with 500 man-days of labor available.

	|      crop      |   yield ($/acre)  |  labor (man-days/acre)  |
	|----------------|-------------------|--------------------------|
	|    tomatoes    |        450        |            6             |
	| green Peppers  |        360        |            7             |
	|   cucumbers    |        400        |            5             |

	Variables:
		- tomatoes: acres allocated to tomatoes.
		- peppers: acres allocated to green peppers.
		- cucumbers: acres allocated to cucumbers.

	Objective:
		Maximize profit (yield per acre) while respecting land and labor constraints. Fertilizer costs are identical for all crops and thus excluded.

	Constraints:
		1. Total acres less equal than 200.
		2. Total labor less equal than 500 man-days.
*/
var int: tomatoes;
var int: peppers;
var int: cucumbers;
var float: c;

constraint tomatoes + peppers + cucumbers <= 200;
constraint 6 * tomatoes + 7 * peppers + 5 * cucumbers <= 500;

constraint c = 450 * tomatoes + 360 * peppers + 400 * cucumbers;
solve maximize c;

constraint tomatoes >= 0;
constraint peppers >= 0;
constraint cucumbers >= 0;

output ["tomatoes: ", show(tomatoes), " acres\n",
		"green peppers: ", show(peppers), " acres\n",
		"cucumbers: ", show(cucumbers), " acres\n",
		"Total profit: $", show(c)];
