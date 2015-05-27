#include "../header/gaussian_filter.h"

#ifndef PI
#define PI 3.1415
#endif /* PI */

#include <math.h>

static double g_sigma = 1.0;
static double g_two_sigma_square = 1.0;
static double g_const_part = 1.0;

double gaussian_filter_calc_with_sigma(const double x, const double y, const double sigma)
{
  double two_sigma_square = 2 * sigma * sigma;
  return 1 / (PI * two_sigma_square) * exp(-((x * x) + (y * y)) / two_sigma_square);
}

double gaussian_filter_calc(const double x, const double y)
{
  return g_const_part * exp(-((x * x) + (y * y)) / g_two_sigma_square);
}

void gaussian_filter_set_sigma(const double sigma)
{
  g_sigma = sigma;
  g_two_sigma_square = 2 * sigma * sigma;
  g_const_part = 1 / (PI * g_two_sigma_square);
}

double gaussian_filter_get_sigma(void)
{
  return g_sigma;
}

#undef PI
