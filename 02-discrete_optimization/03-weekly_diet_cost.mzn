/*
	Determine the lowest weekly cost to meet nutritional requirements for an adult:
		- Minimum weekly needs: 550g protein, 600g fats, 2,000g carbohydrates.

	Food options (nutritional content and cost per 100g):
		- Bread:   8% protein, 1% fat, 55% carbs, $0.25
		- Butter:  0% protein, 90% fat, 0% carbs, $0.50
		- Cheese: 25% protein, 36% fat, 0% carbs, $1.20
		- Cereal: 12% protein, 3% fat, 75% carbs, $0.60
		- Diet Bar: 8% protein, 0% fat, 50% carbs, $1.50

	Variables:
		- Quantity (in grams) of each food to purchase weekly.

	Objective: minimize total cost while satisfying all nutritional constraints.
*/
var float: bread;
var float: butter;
var float: cheese;
var float: cereal;
var float: dietbar;
var float: c;

constraint 0.08 * bread + 0.25 * cheese + 0.12 * cereal + 0.08 * dietbar >= 550;
constraint 0.01 * bread + 0.9 * butter + 0.36 * cheese + 0.03 * cereal >= 600;
constraint 0.55 * bread + 0.75 * cereal + 0.5 * dietbar >= 2000;

constraint bread >= 0;
constraint butter >= 0;
constraint cheese >= 0;
constraint cereal >= 0;
constraint dietbar >= 0;

constraint c = 0.25 * bread + 0.5 * butter + 1.2 * cheese + 0.6 * cereal + 1.5 * dietbar; % Division by 100 can be ommited
solve minimize c;

output ["Bread: ", show(bread), "g\n",
		"Butter: ", show(butter), "g\n",
		"Cheese: ", show(cheese), "g\n",
		"Cereal: ", show(cereal), "g\n",
		"Diet bar: ", show(dietbar), "g\n",
		"Total cost: $", show(c / 100)];
