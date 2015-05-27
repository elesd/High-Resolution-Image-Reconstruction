/**
* @file hrir_mutations.h
* File which contains mutations for hrir.
*/
#ifndef HRIR_MUTATIONS_H
#define HRIR_MUTATIONS_H

#include <ai_evol/list.h>
#include <ai_evol/priority_queue.h>


/**
* Setup of mutation functions global parameters.
* @param element_to_compare The number of top elements to
* use during mutations, like avg, max, ... [default: 2]
* @param gaussian_inc_step Measure of increasing in case of 
* gaussian increase mutation. [default: 0.3]
* @param gaussian_dec_step Measure of decreasing in case of 
* gaussian decreasing mutation. [default: [0.2]
*/
void
hrir_mutations_set_parameters(unsigned element_to_compare,
                              double gaussian_inc_step,
                              double gaussian_dec_step);

/*********************************************************/

/**
* @brief Mutation for Gaussian parameter.
* Get the avg of the bests.
* @param population the population
* @param level: This parameter has no effect to this mutation.
* @return The list of the new elements.
*/
list_LIST
hrir_mutations_gaussian_avg(priority_queue_QUEUE* population,
                            unsigned level);

/*********************************************************/

/**
* @brief Mutation for Gaussian parameter.
* Get the max of the bests.
* @param population the population
* @param level: This parameter has no effect to this mutation.
* @return The list of the new elements.
*/
list_LIST
hrir_mutations_gaussian_max(priority_queue_QUEUE* population,
                            unsigned level);

/*********************************************************/

/**
* @brief Mutation for Gaussian parameter.
* Get the min of the bests.
* @param population the population
* @param level: This parameter has no effect to this mutation.
* @return The list of the new elements.
*/
list_LIST
hrir_mutations_gaussian_min(priority_queue_QUEUE* population,
                            unsigned level);

/*********************************************************/

/**
* @brief Mutation for Gaussian parameter.
* Increase the gaussian param.
* @param population the population
* @param level: Due to this parameter the increment value became 10% less.
* @return The list of the new elements.
*/
list_LIST
hrir_mutations_gaussian_inc(priority_queue_QUEUE* population,
                            unsigned level);

/*********************************************************/

/**
* @brief Mutation for Gaussian parameter.
* Decriese the gaussian param.
* @param population the population
* @param level: Due to this parameter the decrement value became 10% less.
* @return The list of the new elements.
*/
list_LIST
hrir_mutations_gaussian_dec(priority_queue_QUEUE* population,
                            unsigned level);

/*********************************************************/

/**
* @brief Mutation for the filter size.
* Incriese the filter size.
* @param population the population
* @return The list of the new elements.
*/
list_LIST
hrir_mutations_filter_size_inc(priority_queue_QUEUE* population,
                               unsigned level);

/*********************************************************/

/**
* @brief Mutation for the filter size.
* Decriese the filter size.
* @param population the population
* @param level: This parameter has no effect to this mutation.
* @return The list of the new elements.
*/
list_LIST
hrir_mutations_filter_size_dec(priority_queue_QUEUE* population,
                               unsigned level);

/*********************************************************/

/**
* @brief Random mutation.
* Randomize the scale function.
* @param population the population
* @param level: This parameter has no effect to this mutation.
* @return The list of the new elements.
*/
list_LIST
hrir_mutations_random_scale(priority_queue_QUEUE* population,
                            unsigned level);


#endif
