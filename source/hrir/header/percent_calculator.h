/**
* @file percent_calculator.h
* Percentage calculator.
*/
#ifndef PERCENT_CALCULATOR_H
#define PERCENT_CALCULATOR_H

/**
* @brief minimum and maximum value of percentage calculator.
*/
typedef struct
{
  /** Possible lowest value */
	int min;
  /** Possible highest value */
	int max;
} percent_calculator_CALCULATOR;
/**********************************************************************/
/**
* @brief Calculates the precentage of the given value in the given system.
* @param act_value actual value.
* @param calc the given environment
*/
float
percent_calculator_calc
(
  const int act_value,
	const percent_calculator_CALCULATOR calc
);

#endif

