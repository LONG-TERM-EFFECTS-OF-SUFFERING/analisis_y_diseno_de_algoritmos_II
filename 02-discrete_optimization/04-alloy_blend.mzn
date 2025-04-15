/*
	An alloy manufacturer needs to produce 1000 kg of an alloy with:
		- 25%% metal A (250 kg)
		- 75%% metal B (750 kg)
	by blending 5 available alloys. Specifications:

	| alloy | %A  | %B  | available (kg) | price ($/kg) |
	|-------|-----|-----|----------------|--------------|
	|   1   | 10  | 90  |      300       |      6       |
	|   2   | 15  | 85  |      400       |      10      |
	|   3   | 20  | 80  |      200       |      18      |
	|   4   | 30  | 70  |      700       |      24      |
	|   5   | 40  | 60  |      450       |      30      |

	Variables:
		- Quantity (kg) of each alloy to use (alloy_1, alloy_2, ..., alloy_5).

	Objective: minimize total cost while meeting composition and quantity constraints.

	Constraints:
		- Total alloy produced = 1000 kg.
		- Total metal A = 250 kg (25% of 1000 kg).
		- Total metal B = 750 kg (75% of 1000 kg).
		- Do not exceed available quantities for each alloy.
*/
var float: alloy_1;
var float: alloy_2;
var float: alloy_3;
var float: alloy_4;
var float: alloy_5;

constraint alloy_1 + alloy_2 + alloy_3 + alloy_4 + alloy_5 = 1000;
constraint 0.1 * alloy_1 + 0.15 * alloy_2 + 0.2 * alloy_3 + 0.3 * alloy_4 + 0.4 * alloy_5 = 250;
constraint 0.9 * alloy_1 + 0.85 * alloy_2 + 0.8 * alloy_3 + 0.7 * alloy_4 + 0.6 * alloy_5 = 750;
constraint alloy_1 <= 300;
constraint alloy_2 <= 400;
constraint alloy_3 <= 200;
constraint alloy_4 <= 700;
constraint alloy_5 <= 450;

constraint alloy_1 >= 0;
constraint alloy_2 >= 0;
constraint alloy_3 >= 0;
constraint alloy_4 >= 0;
constraint alloy_5 >= 0;

solve minimize 6 * alloy_1 + 10 * alloy_2 + 18 * alloy_3 + 24 * alloy_4 + 30 * alloy_5;

output ["Alloy 1: ", show(alloy_1), "kg\n",
		"Alloy 2: ", show(alloy_2), "g\n",
		"Alloy 3: ", show(alloy_3), "g\n",
		"Alloy 4: ", show(alloy_4), "g\n",
		"Alloy 5: ", show(alloy_5), "g\n"];
