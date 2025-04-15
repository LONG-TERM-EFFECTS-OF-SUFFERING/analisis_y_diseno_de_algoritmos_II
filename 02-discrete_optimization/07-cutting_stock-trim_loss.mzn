/*
	A paper factory must cut jumbo rolls (1000mm) to fulfill an order:
		- 400 reels of 180mm.
		- 200 reels of 260mm.
		- 300 reels of 300mm.

	Each cut must include at least one 300mm reel. Combinations and their trim loss:

	| combination | 300mm | 260mm | 180mm | trim (mm) |
	|-------------|-------|-------|-------|-----------|
	|      1      |   3   |   0   |   0   |    100    |
	|      2      |   2   |   1   |   0   |    140    |
	|      3      |   2   |   0   |   2   |     40    |
	|      4      |   1   |   2   |   1   |      0    |
	|      5      |   1   |   1   |   2   |     80    |
	|      6      |   1   |   0   |   3   |    160    |

	Variables:
		x_1, x_2, x_3, x_4, x_5, x_6: number of times each combination is used.

	Objective: minimize total trim loss while meeting demand.
*/

var int: x_1;
var int: x_2;
var int: x_3;
var int: x_4;
var int: x_5;
var int: x_6;
var int: x_7;
var int: x_8;
var int: x_9;
var int: waste;

constraint 2 * x_3 + x_4 + 2 * x_5 + 3 * x_6 - x_7 = 400; % x_7 = total 180mm reels produced - 400
constraint x_2 + 2 * x_4 + x_5 - x_8 = 200; % x_8 = total 260mm reels produced - 200
constraint 3 * x_1 + 2 * x_2 + 3 * x_3 + x_4 + x_5 + x_6 - x_9 = 300; % x_9 = total 300mm reels produced - 300

constraint x_1 >= 0;
constraint x_2 >= 0;
constraint x_3 >= 0;
constraint x_4 >= 0;
constraint x_5 >= 0;
constraint x_6 >= 0;
constraint x_7 >= 0;
constraint x_8 >= 0;
constraint x_9 >= 0;

constraint waste = 100 * x_1 + 140 * x_2 + 40 * x_3 + 80 * x_5 + 160 * x_6 + 180 * x_7 + 260 * x_8 + 300 * x_8;
solve minimize waste;

output ["combination 1: ", show(x_1), "\n",
		"combination 2: ", show(x_2), "\n",
		"combination 3: ", show(x_3), "\n",
		"combination 4: ", show(x_4), "\n",
		"combination 5: ", show(x_5), "\n",
		"combination 6: ", show(x_6), "\n",
		"180mm overproduced: ", show(x_7), "\n",
		"260mm overproduced: ", show(x_8), "\n",
		"300mm overproduced: ", show(x_9), "\n",
		"total trim loss: ", show(waste)];
