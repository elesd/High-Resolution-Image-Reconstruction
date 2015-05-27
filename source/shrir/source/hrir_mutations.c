#include "../header/hrir_mutations.h"

#include "../header/hrir_ai.h"
#include "../header/compile_uti.h"
#include <hrir/image_filter.h>
#include <ai_evol/list.h>
#include <ai_evol/priority_queue.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

#define LIST_ELEMENT_TO_HRIR_ELEMENT(node)\
((hrir_ai_ELEMENT*)((ai_evol_ELEMENT*)((node)->element))->element)

static unsigned g_element_to_compare = 2;
static double g_gaussian_inc_step = 0.3;
static double g_gaussian_dec_step = 0.2;
static unsigned g_filter_size_step = 2;

void
hrir_mutations_set_parameters(unsigned element_to_compare,
                              double gaussian_inc_step,
                              double gaussian_dec_step)
{
  g_element_to_compare = element_to_compare;
  g_gaussian_inc_step = gaussian_inc_step;
  g_gaussian_dec_step = gaussian_dec_step;
}

/*********************************************************/

list_LIST
hrir_mutations_gaussian_avg(priority_queue_QUEUE* population,
                            unsigned level)
{
  list_LIST ret;
  list_LIST list = priority_queue_to_list(population);
  struct list_NODE* node = list.first_element;
  unsigned counter = 0;
  double avg = 0;
  struct list_NODE* best_gaussian = NULL;
  IGNORE_UNUSED_WARIABLE(level);

  assert(priority_queue_current_size(population) > 0);
  DEBUG_UTIL_TRACE(3, "create mutations with hrir_mutations_gaussian_avg\n", 0);

  while (node != NULL 
         && counter < g_element_to_compare)
  {
    hrir_ai_ELEMENT* hrir_element = LIST_ELEMENT_TO_HRIR_ELEMENT(node);
    image_reconstruct_PARAMETERS param = hrir_element->param;
    if (param.type == IMAGE_RECONSTRUCT_GAUSSIAN)
    {
      avg += param.params.gaussian_sigma;
      if (best_gaussian == NULL)
        best_gaussian = node;
      counter++;
    }
    node = node->next;
  }
  list_init_like(&ret, &list);
  DEBUG_UTIL_DEBUG(2, "create return list\n", 0);
  if (best_gaussian)
  {
    ai_evol_ELEMENT new_element;
    hrir_ai_ELEMENT new;
    new = *LIST_ELEMENT_TO_HRIR_ELEMENT(best_gaussian);
    new.param.params.gaussian_sigma = avg/counter;
    DEBUG_UTIL_TRACE_ELEMENT(3, &new.param,
                             image_reconstruct_trace_parameter);
    new_element.element = &new;
    list_add_element(&ret, &new_element);
  }
  list_destroy(&list);
  return ret;
}

/*********************************************************/

list_LIST
hrir_mutations_gaussian_max(priority_queue_QUEUE* population,
                            unsigned level)
{
  list_LIST ret;
  list_LIST list = priority_queue_to_list(population);
  struct list_NODE* node = list.first_element;
  unsigned counter = 0;
  double max_val = INT_MIN;
  struct list_NODE* best_gaussian = NULL;
  IGNORE_UNUSED_WARIABLE(level);

  assert(priority_queue_current_size(population) > 0);
  DEBUG_UTIL_TRACE(3, "create mutations with hrir_mutations_gaussian_max\n", 0);

  while (node != NULL 
         && counter < g_element_to_compare)
  {
    hrir_ai_ELEMENT* hrir_element = LIST_ELEMENT_TO_HRIR_ELEMENT(node); 
    image_reconstruct_PARAMETERS param = hrir_element->param;
    if (param.type == IMAGE_RECONSTRUCT_GAUSSIAN)
    {
      max_val = max(param.params.gaussian_sigma, max_val);
      if (best_gaussian == NULL)
        best_gaussian = node;
      counter++;
    }
    node = node->next;
  }
  list_init_like(&ret, &list);
  DEBUG_UTIL_DEBUG(2, "create return list\n", 0);
  if (best_gaussian)
  {
    ai_evol_ELEMENT new_element;
    hrir_ai_ELEMENT new;
    new = *LIST_ELEMENT_TO_HRIR_ELEMENT(best_gaussian);
    new.param.params.gaussian_sigma = max_val;
    DEBUG_UTIL_TRACE_ELEMENT(3, &new.param,
                             image_reconstruct_trace_parameter);
    new_element.element = &new;
    list_add_element(&ret, &new_element);
  }
  list_destroy(&list);
  return ret;
}

/*********************************************************/

list_LIST
hrir_mutations_gaussian_min(priority_queue_QUEUE* population,
                            unsigned level)
{
  list_LIST ret;
  list_LIST list = priority_queue_to_list(population);
  struct list_NODE* node = list.first_element;
  unsigned counter = 0;
  double min_val = INT_MAX;
  struct list_NODE* best_gaussian = NULL;
  IGNORE_UNUSED_WARIABLE(level);

  assert(priority_queue_current_size(population) > 0);
  DEBUG_UTIL_TRACE(3, "create mutations with hrir_mutations_gaussian_min\n", 0);

  while (node != NULL 
         && counter < g_element_to_compare)
  {
    hrir_ai_ELEMENT* hrir_element = LIST_ELEMENT_TO_HRIR_ELEMENT(node);
    image_reconstruct_PARAMETERS param = hrir_element->param; 
    if (param.type == IMAGE_RECONSTRUCT_GAUSSIAN)
    {
      min_val = min(param.params.gaussian_sigma, min_val);
      if (best_gaussian == NULL)
        best_gaussian = node;
      counter++;
    }
    node = node->next;
  }
  list_init_like(&ret, &list);
  DEBUG_UTIL_DEBUG(2, "create return list\n", 0);
  if (best_gaussian)
  {
    ai_evol_ELEMENT new_element;
    hrir_ai_ELEMENT new;
    new = *LIST_ELEMENT_TO_HRIR_ELEMENT(best_gaussian);
    new.param.params.gaussian_sigma = min_val;
    DEBUG_UTIL_TRACE_ELEMENT(3, &new.param,
                             image_reconstruct_trace_parameter);
    new_element.element = &new;
    list_add_element(&ret, &new_element);
  }
  list_destroy(&list);
  return ret;
}

/*********************************************************/

list_LIST
hrir_mutations_gaussian_inc(priority_queue_QUEUE* population,
                            unsigned level)
{
  list_LIST ret;
  list_LIST list = priority_queue_to_list(population);
  struct list_NODE* node = list.first_element;
  struct list_NODE* best_gaussian = NULL;

  assert(priority_queue_current_size(population) > 0);
  DEBUG_UTIL_TRACE(3, "create mutations with hrir_mutations_gaussian_inc\n", 0);

  while (node != NULL)
  {
    hrir_ai_ELEMENT* hrir_element = LIST_ELEMENT_TO_HRIR_ELEMENT(node);
    image_reconstruct_PARAMETERS param = hrir_element->param;
    if (param.type == IMAGE_RECONSTRUCT_GAUSSIAN)
    {
      if (best_gaussian == NULL)
      {
        best_gaussian = node;
        break;
      }
    }
    node = node->next;
  }
  list_init_like(&ret, &list);
  DEBUG_UTIL_DEBUG(2, "create return list\n", 0);
  if (best_gaussian)
  {
    ai_evol_ELEMENT new_element;
    hrir_ai_ELEMENT new;
    double step = level == 0 ? g_gaussian_inc_step
                             : g_gaussian_inc_step / (double)pow(10, -level);
    step = max(0.001, step);
    new = *LIST_ELEMENT_TO_HRIR_ELEMENT(best_gaussian);
    new.param.params.gaussian_sigma += step;
    DEBUG_UTIL_TRACE_ELEMENT(3, &new.param,
                             image_reconstruct_trace_parameter);
    new_element.element = &new;
    list_add_element(&ret, &new_element);
  }
  list_destroy(&list);
  return ret;
}

/*********************************************************/

list_LIST
hrir_mutations_gaussian_dec(priority_queue_QUEUE* population,
                            unsigned level)
{
  list_LIST ret;
  list_LIST list = priority_queue_to_list(population);
  struct list_NODE* node = list.first_element;
  struct list_NODE* best_gaussian = NULL;

  IGNORE_UNUSED_WARIABLE(level);
  assert(priority_queue_current_size(population) > 0);
  DEBUG_UTIL_TRACE(3, "create mutations with hrir_mutations_gaussian_dec\n", 0);

  while (node != NULL)
  {
    hrir_ai_ELEMENT* hrir_element = LIST_ELEMENT_TO_HRIR_ELEMENT(node);
    image_reconstruct_PARAMETERS param = hrir_element->param;
    if (param.type == IMAGE_RECONSTRUCT_GAUSSIAN)
    {
      if (best_gaussian == NULL)
      {
        best_gaussian = node;
        break;
      }
    }
    node = node->next;
  }
  list_init_like(&ret, &list);
  DEBUG_UTIL_DEBUG(2, "create return list\n", 0);
  if (best_gaussian)
  {
    ai_evol_ELEMENT new_element;
    hrir_ai_ELEMENT new;

    double step = level == 0 ? g_gaussian_inc_step
                             : g_gaussian_inc_step / (double)(level * 10);
    step = max(0.001, step);
    
    new = *LIST_ELEMENT_TO_HRIR_ELEMENT(best_gaussian);
    new.param.params.gaussian_sigma -= step;
    
    new.param.params.gaussian_sigma = 
      max(0, new.param.params.gaussian_sigma);

    DEBUG_UTIL_TRACE_ELEMENT(3, &new.param,
                             image_reconstruct_trace_parameter);
    new_element.element = &new;
    list_add_element(&ret, &new_element);
  }
  list_destroy(&list);
  return ret;
}

/*********************************************************/

list_LIST
hrir_mutations_filter_size_inc(priority_queue_QUEUE* population,
                               unsigned level)
{
  list_LIST ret;
  list_LIST list = priority_queue_to_list(population);
  struct list_NODE* node = list.first_element;
  struct list_NODE* best = NULL;

  IGNORE_UNUSED_WARIABLE(level);
  assert(priority_queue_current_size(population) > 0);
  DEBUG_UTIL_TRACE(3, "create mutations with hrir_mutations_filter_size_inc\n", 0);

  while (node != NULL)
  {
    hrir_ai_ELEMENT* hrir_element = LIST_ELEMENT_TO_HRIR_ELEMENT(node);
    image_reconstruct_PARAMETERS param = hrir_element->param;
    if (param.type != IMAGE_RECONSTRUCT_NON_MAXIMA)
    {
      best = node;
      break;
    }
    node = node->next;
  }
  list_init_like(&ret, &list);
  DEBUG_UTIL_DEBUG(2, "create return list\n", 0);
  if (best)
  {
    ai_evol_ELEMENT new_element;
    hrir_ai_ELEMENT new;
    new = *LIST_ELEMENT_TO_HRIR_ELEMENT(best);
    new.param.size += g_filter_size_step;
    new.param.size = min(new.param.size, 10);
    DEBUG_UTIL_TRACE_ELEMENT(3, &new.param,
                             image_reconstruct_trace_parameter);
    new_element.element = &new;
    list_add_element(&ret, &new_element);
  }
  list_destroy(&list);
  return ret;
}

/*********************************************************/

list_LIST
hrir_mutations_filter_size_dec(priority_queue_QUEUE* population,
                               unsigned level)
{
  list_LIST ret;
  list_LIST list = priority_queue_to_list(population);
  struct list_NODE* node = list.first_element;
  struct list_NODE* best = NULL;

  IGNORE_UNUSED_WARIABLE(level);
  assert(priority_queue_current_size(population) > 0);
  DEBUG_UTIL_TRACE(3, "create mutations with hrir_mutations_filter_size_dec\n", 0);

  while (node != NULL)
  {
    hrir_ai_ELEMENT* hrir_element = LIST_ELEMENT_TO_HRIR_ELEMENT(node);
    image_reconstruct_PARAMETERS param = hrir_element->param;
    if (param.type != IMAGE_RECONSTRUCT_NON_MAXIMA)
    {
      best = node;
      break;
    }
    node = node->next;
  }
  list_init_like(&ret, &list);
  DEBUG_UTIL_DEBUG(2, "create return list\n", 0);
  if (best)
  {
    ai_evol_ELEMENT new_element;
    hrir_ai_ELEMENT new;
    new = *LIST_ELEMENT_TO_HRIR_ELEMENT(best);
    new.param.size -= g_filter_size_step;
    new.param.size = max(1, new.param.size);
    DEBUG_UTIL_TRACE_ELEMENT(3, &new.param,
                             image_reconstruct_trace_parameter);
    new_element.element = &new;
    list_add_element(&ret, &new_element);
  }
  list_destroy(&list);
  return ret;
}

/*********************************************************/

list_LIST
hrir_mutations_random_scale(priority_queue_QUEUE* population,
                            unsigned level)
{
  list_LIST ret;
  priority_queue_ELEMENT node = priority_queue_first(population);
  ai_evol_ELEMENT new_element;
  hrir_ai_ELEMENT new;
  unsigned method;
  IGNORE_UNUSED_WARIABLE(level);
  /* TODO: Not so efficient, only for copy purpose */
  list_LIST list = priority_queue_to_list(population);
  
  new = *LIST_ELEMENT_TO_HRIR_ELEMENT(&node);
  
  assert(priority_queue_current_size(population) > 0);
  DEBUG_UTIL_TRACE(3, "create mutations with hrir_mutations_random_scale\n", 0);
  
  srand(time(0));
  method = rand() % IMAGE_RECONSTRUCT_NUM_OF_SCALE_METHOD;
  new.param.scaling = (image_reconstruct_SCALE_METHOD)method;
  new_element.element = &new;
  DEBUG_UTIL_TRACE_ELEMENT(3, &new.param,
                           image_reconstruct_trace_parameter);

  list_init_like(&ret, &list);
  DEBUG_UTIL_DEBUG(2, "create return list\n", 0);
  list_add_element(&ret, &new_element);
  return ret;
}

