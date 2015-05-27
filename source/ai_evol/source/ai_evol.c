#include "../header/ai_evol.h"
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include <debug_util/debug.h>

#define MAX(a, b) ( ( (a) > (b) ) ? (a) : (b) )

/******************************************************************************/

static void
copy_state(ai_evol_STATE* result, 
           const ai_evol_STATE* input);

/******************************************************************************/

static void
calculate_rank(ai_evol_STATE* result,
               const ai_evol_STATE* input);

/******************************************************************************/

static void
sort_and_keep(ai_evol_STATE* result);

/******************************************************************************/

static void
mutate_elements(ai_evol_STATE* result);

/******************************************************************************/

static void
default_destroy(void* element);

/******************************************************************************/

static ai_evol_STATE 
whole_copy_of_state(const ai_evol_STATE* state);

/******************************************************************************/

ai_evol_STATE
ai_evol_iterate(const ai_evol_STATE* state)
{
  ai_evol_STATE ret;

  assert(state != NULL);

  copy_state(&ret, state);
  calculate_rank(&ret, state);
  sort_and_keep(&ret);
  mutate_elements(&ret);
  ret.phase_counter++;
  return ret;
}

/******************************************************************************/

ai_evol_STATE
ai_evol_create_state(list_LIST* mutations,
                     priority_queue_QUEUE* population,
                     unsigned keep_counter,
                     unsigned iteration_per_level,
                     ai_evol_RANK_FUNCTION rank_function,
                     ai_evol_DESTROY_FUNC destroy_func)
{
  ai_evol_STATE ret;
  ret.mutations = *mutations;
  ret.population = *population;
  ret.keep_counter = keep_counter;
  ret.phase_counter = 0;
  ret.iteration_per_level = iteration_per_level;
  ret.rank_function = rank_function;
  ret.destroy_func = destroy_func ? destroy_func : &default_destroy;
  return ret;
}

/******************************************************************************/

ai_evol_STATE
ai_evol_start(const ai_evol_STATE* start_phase,
              const unsigned max_iteration,
              const int target_value)
{
  ai_evol_STATE best = whole_copy_of_state(start_phase);
  ai_evol_STATE current_state = whole_copy_of_state(start_phase);
  unsigned phase_counter = 0;
  int best_rank;
  assert(start_phase != NULL);

  best_rank = priority_queue_first(&start_phase->population).rank;
  while (phase_counter < max_iteration
         && target_value > best_rank)
  {
    int current_rank;
    
    /* swap the two state */
    {
      ai_evol_STATE next_state = ai_evol_iterate(&current_state);
      /* Not necessary from now */
      ai_evol_destroy_state(&current_state);
      current_state = next_state;
    }

    DEBUG_UTIL_TRACE(0, "phase counter: %u [%u] on level %u\n", phase_counter, max_iteration, phase_counter / current_state.iteration_per_level);

    DEBUG_UTIL_TRACE(0, "best rank: %d | target value: [%d]\n",
                     best_rank, target_value);

    current_rank = priority_queue_first(&current_state.population).rank;
    if (best_rank < current_rank)
    {
      DEBUG_UTIL_TRACE(1, "best found: %d < %d\n", best_rank, current_rank);
      best_rank = current_rank;
      /* New best is found old can be released */
      ai_evol_destroy_state(&best);
      best = whole_copy_of_state(&current_state);
    }

    DEBUG_UTIL_TRACE(0, "swap element to delete\n", 0);

    phase_counter++;
  }
  ai_evol_destroy_state(&current_state);

  return best;
}

/******************************************************************************/

void
ai_evol_destroy_state(ai_evol_STATE* state)
{
  assert(state != NULL);
  DEBUG_UTIL_DEBUG(0, "Destroy state: phase_counter %d\n", state->phase_counter);

  list_destroy(&state->mutations);
  priority_queue_destroy(&state->population);
}

/******************************************************************************/

static void
copy_state(ai_evol_STATE* result, 
           const ai_evol_STATE* input)
{
  assert(result != NULL);
  assert(input != NULL);
  assert(priority_queue_capacity(&input->population) > input->keep_counter);
  result->destroy_func = input->destroy_func;

  /* only init the queue, values will be filled up in calculate_rank 
  *  function
  */
  priority_queue_init_like(&result->population,
                           &input->population);
  result->mutations = list_copy(&input->mutations);
  result->keep_counter = input->keep_counter;
  result->phase_counter = input->phase_counter;
  result->iteration_per_level = input->iteration_per_level;
  result->rank_function = input->rank_function;
}

/******************************************************************************/

static void
calculate_rank(ai_evol_STATE* result,
               const ai_evol_STATE* input)
{
  assert(input != NULL);
  assert(result != NULL);
  DEBUG_UTIL_TRACE(1, "calculate rank\n",0);
  {
    struct list_NODE* element_node;
    list_LIST population = priority_queue_to_list(&input->population);
    /* calc rank of the population */
    element_node = population.first_element;
    assert(element_node != NULL);
    while (element_node != NULL)
    {
      ai_evol_ELEMENT* act_element = 
        (ai_evol_ELEMENT*)element_node->element;

      act_element->rank = input->rank_function(act_element);
      DEBUG_UTIL_TRACE(3, "  rank: %d\n",act_element->rank);
      priority_queue_insert(&result->population,
                            act_element, act_element->rank);

      element_node = element_node->next;
    }
    list_destroy(&population);
  }
}

/******************************************************************************/

static void
sort_and_keep(ai_evol_STATE* result)
{
  assert(result != NULL);
  {
    unsigned population_size
      = priority_queue_current_size(&result->population);
    priority_queue_pop_back(&result->population,
                            MAX(population_size - result->keep_counter, 0));

  while (result->keep_counter < priority_queue_current_size(&result->population))
  {
    priority_queue_pop(&result->population);
  }
  }
}

/******************************************************************************/

static void
mutate_elements(ai_evol_STATE* result)
{
  struct list_NODE* act_element;
  list_LIST new_elements;
  ai_evol_MUTATION_METHOD_ID id = 0;
  list_LIST population = priority_queue_to_list(&result->population);

  assert(result != NULL);
  DEBUG_UTIL_TRACE(1, "Create mutations\n", 0);
  
  /* TODO: not so efficient create only for copy purpose */
  list_init_like(&new_elements,
                 &population);
  
  act_element = result->mutations.first_element;
  assert(act_element);
  while (act_element != NULL)
  {
    list_LIST result_list;
    struct list_NODE* new_element_node;
    ai_evol_MUTATION mutation = 
      ((ai_evol_MUTATION_ELEMENT*)act_element->element)->mutation;
    result_list = mutation(&result->population,
                           result->phase_counter 
                             / result->iteration_per_level);

    assert(priority_queue_capacity(&result->population) 
           > list_size(&result_list) 
             + priority_queue_current_size(&result->population));

    new_element_node = result_list.first_element;
    if (new_element_node == NULL)
    {
      DEBUG_UTIL_TRACE(1, "Mutation has no effect %d\n", id);
    }
    while (new_element_node != NULL)
    {
      ai_evol_ELEMENT* new_element = (ai_evol_ELEMENT*)new_element_node->element;
      DEBUG_UTIL_TRACE(1, "Create new element in phase %u with id: %d\n", result->phase_counter, id);
      new_element->method_id = id;
      new_element->rank = INT_MIN;
      new_element->creation_phase = result->phase_counter;
      list_add_element(&new_elements, new_element);
      new_element_node = new_element_node->next;
    }
    ++id;
    list_destroy(&result_list);
    act_element = act_element->next;
  }
  {
    struct list_NODE* new_element = new_elements.first_element;
    DEBUG_UTIL_TRACE(1, "New population: %u + %u\n",
        priority_queue_current_size(&result->population),
        list_size(&new_elements));
    while (new_element != NULL)
    {
      priority_queue_insert(&result->population,
                            new_element->element,
                            INT_MIN); /* rank */
      new_element = new_element->next;
    }
  }
  list_destroy(&new_elements);
}

/******************************************************************************/

static void
default_destroy(void* element)
{
  ai_evol_ELEMENT* deleted = element;
  DEBUG_UTIL_DEBUG(0, "Destroy mutation element\n", 0);
  free(deleted->element);
}

/******************************************************************************/

static ai_evol_STATE 
whole_copy_of_state(const ai_evol_STATE* input)
{
  ai_evol_STATE result;
  assert(input != NULL);
  result.destroy_func = input->destroy_func;
  result.population = priority_queue_copy(&input->population);
  result.mutations = list_copy(&input->mutations);
  result.keep_counter = input->keep_counter;
  result.phase_counter = input->phase_counter;
  result.iteration_per_level = input->iteration_per_level;
  result.rank_function = input->rank_function;
  return result;
}

/******************************************************************************/

#undef MAX

