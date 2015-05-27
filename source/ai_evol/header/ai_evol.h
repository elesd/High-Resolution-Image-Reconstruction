/**
  * @file ai_evol.h
  * @brief This file contains an evolution algorithm implementation
  */
#ifndef AI_EVOL
#define AI_EVOL

#include "list.h"
#include "priority_queue.h"
/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
/******************************************************************************/
/* TYPES                                                                      */
/******************************************************************************/
/** @nodoc */
typedef int ai_evol_MUTATION_METHOD_ID;

/*****************************************************************************/

/**
* @brief callback function to destroy an element
* @param element the destroyable element
*/
typedef void (*ai_evol_DESTROY_FUNC)(void* element);

/******************************************************************************/

/**
* Population element
*/
typedef struct
{
  /**
  * Pointer to the element
  */
  void* element;

  /**
  * The rank of the element
  */
  int rank;

  /**
  * The mutation id, who was created this element.
  */
  ai_evol_MUTATION_METHOD_ID method_id;

  /**
  * Phase where it is created
  */
  unsigned creation_phase;

} ai_evol_ELEMENT;

/******************************************************************************/

/**
* Function which calculates the rank of the current element.
* @details determines how much good the current element in the population.
*          Actually this function contains the logic of the algorithm.
* @param element pointer  an element in the population
* @returns the rank of the given element
*/
typedef int (*ai_evol_RANK_FUNCTION)(const ai_evol_ELEMENT* element);
/******************************************************************************/

/**
 * State description
 * @details The descriptor of one iteration of the evolution algorithm
 */
typedef struct 
{
  /** 
   * list for the mutation functions.
   * This list contatains #ai_evol_MUTATION_ELEMENT objects.
   */
  list_LIST mutations;
  /**
   * Stack for the population
   */
  priority_queue_QUEUE population;
  /**
  * The number of bests
  * @details Who many element will be keep between two phase
  */
  unsigned keep_counter;
  /**
  * The current phase id
  */
  unsigned phase_counter;
  
  /**
  * This member tell the algorithm how much iteration will be done on the same
  * level.
  * The first level is the 0.
  */
  unsigned iteration_per_level;

  /**
  * function to calculate rank
  */
  ai_evol_RANK_FUNCTION rank_function;

  /**
  * Destroy function for the content of an #ai_evol_ELEMENT
  * @see #ai_evol_ELEMENT.element
  */
  ai_evol_DESTROY_FUNC destroy_func;
  
} ai_evol_STATE;

/******************************************************************************/

/**
* Mutation method.
* This function works on the population list.
* @param[in] population the startup population
* @param level: level of the mutation. Mutations can be work in different way 
*               on different levels.
* @returns the list of ai_evol_ELEMENT, actually the list of the new elements.
*/
typedef list_LIST (*ai_evol_MUTATION)(priority_queue_QUEUE* population,
                                      unsigned level);

/**
* Type for holding mutations.
* This type has to be the content of mutations
*/
typedef struct
{
  /**
  * Function pointer for mutations
  */
  ai_evol_MUTATION mutation;
} ai_evol_MUTATION_ELEMENT;

/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/

/**
* Creates a new state based on the given values.
* @param mutations list of mutation methodes (#ai_evol_MUTATION)
* @param population priority queue of #ai_evol_ELEMENT
* @param keep_counter number of population element which will be keeped 
* between two iteration.
* @param iteration_per_level: maximum number of iterations on one level
* @param rank_function rank function to calculate an #ai_evol_ELEMENT.element's rank
* @param destroy_func function to destroy an #ai_evol_ELEMENT. If it is NULL
* the default behavior is to free the #ai_evol_ELEMENT.element. So actually the
* function's parameter is an ai_evol_ELEMENT*.
* @return a new state
*/
ai_evol_STATE
ai_evol_create_state(list_LIST* mutations,
                     priority_queue_QUEUE* population,
                     unsigned keep_counter,
                     unsigned iteration_per_level,
                     ai_evol_RANK_FUNCTION rank_function,
                     ai_evol_DESTROY_FUNC destroy_func);

/******************************************************************************/

/**
* This function iterate from a start state to a new one.
* The function creates a new state, evaluates the current population, keep the
* bests instance and executes the mutation methods.
* @param state the current state.
*/
ai_evol_STATE
ai_evol_iterate(const ai_evol_STATE* state);

/******************************************************************************/

/**
* Iterates from the start_phase until we reach the target value, or goes over
* the max_iteration.
* @param start_phase the starting phase
* @param max_iteration the maximum number of iterations
* @param target_value the target best value
* @returns The best result
*/
ai_evol_STATE
ai_evol_start(const ai_evol_STATE* start_phase,
              const unsigned max_iteration,
              const int target_value);

/******************************************************************************/

/**
* Destroy the given state.
* @param state Not NULL state.
*/
void
ai_evol_destroy_state(ai_evol_STATE* state);

/******************************************************************************/

/**
* Destroy the given state.
* @param state Not NULL state.
*/
void
ai_evol_destroy_state(ai_evol_STATE* state);
#endif
