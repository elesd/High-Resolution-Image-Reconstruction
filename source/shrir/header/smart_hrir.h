/**
* @file smart_hrir.h
* @brief Smart high-resolution-image-reconstruction.
* Implementation of an evolution algorithm which is
* based on the hrir parameters
*/

#ifndef SMART_HRIR_H
#define SMART_HRIR_H

#include <hrir/image_filter.h>

/*********************************************************/

typedef struct 
{

  /** number of best values to keep. */
  unsigned keep_counter;
  /** The redundancy of basic parameters in the initial population */
  unsigned redundancy;
  /** limit for the evolution algorithm limit */
  unsigned iteration_limit;
  /** the target mse of the algorithm. */
  unsigned iteration_per_level;
  /** the target mse of the algorithm. */
  int target_rank;
} smart_hrir_SETTINGS;

/*********************************************************/
/**
* @brief Start the algorithm to determine the best parameters.
* Determines and also use the best parameter settings,
* and returns the reconstructed image.
* There is a possibility to set up the parameter of mutation
* function. See #hrir_mutations_set_parameters.
* @param input The input image
* @param settings setting of the algorithm.
* @param reached_iteration The number of iteration which was reached.
*                          Optional parameter.
* @param reached_rank The rank which was reached. Optional parameter.
* @return image with double size.
*/
image_filter_IMG
smart_hrir_start_algorithm(const image_filter_IMG* input,
                           smart_hrir_SETTINGS* settings,
                           unsigned* reached_iteration,
                           int* reached_rank);



#endif

