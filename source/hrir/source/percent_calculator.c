#include "../header/percent_calculator.h"

/**********************************************************************/
float 
percent_calculator_calc
(
  const int act_value,
	const percent_calculator_CALCULATOR calc
)
{
	if (calc.max == calc.min)
		return 0.0f;
	return (act_value - calc.min) / (float)(calc.max - calc.min);
}

