/*
	A refinery uses two crude oils to produce gasoline, heating oil, jet fuel, and lube oil:
	- Light crude: $40/barrel.
	- Heavy crude: $30/barrel.

	Production yield per barrel:

	|    product    | light crude | heavy crude |
	|---------------|-------------|-------------|
	|   gasoline    |     0.4     |     0.3     |
	|  heating oil  |     0.2     |     0.45    |
	|   jet fuel    |     0.3     |     0.1     |
	|   lube oil    |     0.1     |     0.05    |

	Demand (million barrels):
		- Gasoline: 8.
		- Heating oil: 6.
		- Jet fuel: 7.
		- Lube oil: 3.

	Variables:
		x: million barrels of light crude.
		y: million barrels of heavy crude.
*/
var int: x;
var int: y;
var float: c;

constraint 0.4 * x + 0.3 * y >= 8;
constraint 0.2 * x + 0.45 * y >= 6;
constraint 0.3 * x + 0.1 * y >= 7;
constraint 0.1 * x + 0.05 * y >= 3;

constraint x >= 0;
constraint y >= 0;

constraint c = 40 * x + 30 * y;
solve minimize c;

output ["x = ", show(x), "\ny = ", show(y), "\nc = ", show(c)]
