/**
* @file gaussian_filter.h
* Gauss filter implementation. 
*/
#ifndef GAUSSIAN_FILTER_H
#define GAUSSIAN_FILTER_H


/**
  * @brief 2 dimensional Gaussian function
  * @details \f$ g(x, y) = \frac{1}{2 \Pi \sigma^2} \cdot exp(-\frac{x^2 + y^2}{2 \sigma^2}) \f$ 
  * @param x the x coordinate
  * @param y the y coordinate
  * @param sigma the sigma parameter
  * @return the result of the gaussian function in the given coordinates.
  */
double gaussian_filter_calc_with_sigma(const double x, const double y, const double sigma);

/****************************************************/

/**
  * @brief 2 dimensional Gaussian function
  * @details \f$ g(x, y) = \frac{1}{2 \Pi \sigma^2} \cdot exp(-\frac{x^2 + y^2}{2 \sigma^2}) \f$ 
  *          In this function calling the sigma parameter cames from the context.
  * @see gaussian_filter_set_sigma
  * @param x the x coordinate
  * @param y the y coordinate
  * @return the result of the gaussian function in the given coordinates.
  * @note This function is faster, but not executable in paralell way!
  */
double gaussian_filter_calc(const double x, const double y);

/****************************************************/

/**
  * @brief Setter for the sigma parameter in the context
  * @param sigma the new sigma value for the context
  */
void gaussian_filter_set_sigma(const double sigma);

/****************************************************/

/**
  * @brief Getter for the sigma parameter in the context
  * @return the sigma value of the context
  */
double gaussian_filter_get_sigma(void);

#endif
