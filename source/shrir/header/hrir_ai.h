/**
* @file hrir_ai.h
* HRIR Ai implementation.
* This module uses an evolution algorithm to increase the
* quality of image resoultion
*/
#ifndef HRIR_AI_H
#define HRIR_AI_H

#include <hrir/image_reconstruct.h>
#include <ai_evol/ai_evol.h>

/*********************************************************/

/**
* @brief Element for the evolution algorithm
*/
typedef struct
{
  /** Pointer to the original image */
  const image_filter_IMG* original_image;
  /** Parameters for the reconstruction */
  image_reconstruct_PARAMETERS param;
} hrir_ai_ELEMENT;

/*********************************************************/

/**
* @brief Create the initial state of the evolution alg.
* @param original_image The error 
* @param keep_counter Number of entity to keep during two iteration .
* @param iteration_per_level: Number of iterations per one level.
* @param redundancy Redundancy of base parameters in the initial
* population.
* @return First state of the algorithm
*/
ai_evol_STATE
hrir_ai_create_init_state(const image_filter_IMG* original_image,
                          unsigned keep_counter,
                          unsigned iteration_per_level,
                          unsigned redundancy);

/*********************************************************/

/**
* @brief Iterate to the next state
* @param phase start phase
* @todo implement it
* @return the next state.
*/
ai_evol_STATE
hrir_ai_iterate(const ai_evol_STATE* phase);

/*********************************************************/


#endif
