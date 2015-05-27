/**
* @file median_filter.h
* Special filter not claclulated with simple mask.
*/

#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

/** @nodoc */
#define MEDIAN_FILTER_MAX_FILTER_SIZE 20

#include <image_filter.h>


/**
  * @brief Apply the median filter.
  * @param img_data the current data in the window
  * @param x the x coordinate of the window
  * @param y the y coordinate of the window
  * @param size the size of the window
  * @return the value of the filter
  */
double
median_filter_apply_filter(const image_filter_IMG_DATA img_data,
                           const double x,
                           const double y,
                           const unsigned size);
                        

#endif
