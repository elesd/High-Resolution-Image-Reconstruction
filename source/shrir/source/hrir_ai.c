#include "../header/hrir_ai.h"

#include "../header/hrir_mutations.h"
#include "../header/compile_uti.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <ai_evol/ai_evol.h>
#include <ai_evol/list.h>
#include <hrir/image_reconstruct.h>
#include <assert.h>
#include <debug_util/debug.h>

#define SIZE_OF_BASE_PARAMS 16
#define REDUNDANCY 2
#define POPULATION_SIZE (REDUNDANCY * SIZE_OF_BASE_PARAMS)

#define CREATE_GAUS_PARAM(sigma, filter_size, scale)\
{\
  {.gaussian_sigma = sigma},\
  IMAGE_RECONSTRUCT_GAUSSIAN,\
  filter_size,\
  scale\
}

#define CREATE_NON_MAX_PARAM(filter_type, scale)\
{\
  {.non_maxima_type = filter_type},\
  IMAGE_RECONSTRUCT_NON_MAXIMA,\
  3,\
  scale \
}

#define CREATE_MEDIAN_PARAM(filter_size, scale)\
{\
  {.gaussian_sigma = 0.0},\
  IMAGE_RECONSTRUCT_MEDIAN,\
  filter_size,\
  scale\
}

/*********************************************************/

static list_LIST
create_mutations(void);

/*********************************************************/

static priority_queue_QUEUE 
create_population(const image_filter_IMG* original_image,
                  unsigned redundancy,
                  unsigned population_size);

/*********************************************************/

static int
calc_rank(const ai_evol_ELEMENT* element);

/*********************************************************/

static void*
copy_ai_element(void* dest, const void *element, size_t size);

/*********************************************************/

static void
delete_ai_element(void* element);

/*********************************************************/

ai_evol_STATE
hrir_ai_create_init_state(const image_filter_IMG* original_image,
                          unsigned keep_counter,
                          unsigned iteration_per_level,
                          unsigned redundancy)
{
  list_LIST mutations = create_mutations();
  priority_queue_QUEUE population = 
    create_population(original_image, redundancy, keep_counter);
  return ai_evol_create_state(&mutations,
                              &population,
                              keep_counter,
                              iteration_per_level,
                              calc_rank,
                              NULL);
}

/*********************************************************/

static list_LIST
create_mutations(void)
{
  list_LIST ret;
  ai_evol_MUTATION_ELEMENT element;
  list_init_list(&ret, sizeof(ai_evol_MUTATION), NULL, NULL);


  element.mutation = hrir_mutations_gaussian_avg;

  list_add_element(&ret, &element);

  element.mutation = hrir_mutations_gaussian_max;
  list_add_element(&ret, &element);

  element.mutation = hrir_mutations_gaussian_min;
  list_add_element(&ret, &element);

  element.mutation = hrir_mutations_gaussian_inc;
  list_add_element(&ret, &element);

  element.mutation = hrir_mutations_gaussian_dec;
  list_add_element(&ret, &element);

  element.mutation = hrir_mutations_filter_size_inc;
  list_add_element(&ret, &element);

  element.mutation = hrir_mutations_filter_size_dec;
  list_add_element(&ret, &element);

  element.mutation = hrir_mutations_random_scale;
  list_add_element(&ret, &element);
  return ret;
}

/*********************************************************/

static priority_queue_QUEUE
create_population(const image_filter_IMG* original_image,
                  unsigned redundancy,
                  unsigned population_size)
{
  priority_queue_QUEUE ret;
  unsigned i, j;
  static image_reconstruct_PARAMETERS basic_params[] =
  {
    CREATE_GAUS_PARAM(0.5, 3, IMAGE_RECONSTRUCT_SCALE_TO_ORIGIN),
    CREATE_GAUS_PARAM(0.5, 3, IMAGE_RECONSTRUCT_SCALE_UP),
    CREATE_GAUS_PARAM(0.5, 3, IMAGE_RECONSTRUCT_SCALE_CUT),
    CREATE_GAUS_PARAM(0.5, 3, IMAGE_RECONSTRUCT_SCALE_AVG),
    CREATE_NON_MAX_PARAM(IMAGE_RECONSTRUCT_SOBEL, IMAGE_RECONSTRUCT_SCALE_AVG),
    CREATE_NON_MAX_PARAM(IMAGE_RECONSTRUCT_SOBEL, IMAGE_RECONSTRUCT_SCALE_UP),
    CREATE_NON_MAX_PARAM(IMAGE_RECONSTRUCT_SOBEL, IMAGE_RECONSTRUCT_SCALE_CUT),
    CREATE_NON_MAX_PARAM(IMAGE_RECONSTRUCT_SOBEL, IMAGE_RECONSTRUCT_SCALE_TO_ORIGIN),
    CREATE_NON_MAX_PARAM(IMAGE_RECONSTRUCT_PREWIT, IMAGE_RECONSTRUCT_SCALE_AVG),
    CREATE_NON_MAX_PARAM(IMAGE_RECONSTRUCT_PREWIT, IMAGE_RECONSTRUCT_SCALE_UP),
    CREATE_NON_MAX_PARAM(IMAGE_RECONSTRUCT_PREWIT, IMAGE_RECONSTRUCT_SCALE_CUT),
    CREATE_NON_MAX_PARAM(IMAGE_RECONSTRUCT_PREWIT, IMAGE_RECONSTRUCT_SCALE_TO_ORIGIN),
    CREATE_MEDIAN_PARAM(3, IMAGE_RECONSTRUCT_SCALE_TO_ORIGIN),
    CREATE_MEDIAN_PARAM(3, IMAGE_RECONSTRUCT_SCALE_UP),
    CREATE_MEDIAN_PARAM(3, IMAGE_RECONSTRUCT_SCALE_CUT),
    CREATE_MEDIAN_PARAM(3, IMAGE_RECONSTRUCT_SCALE_AVG)
  };
  population_size = 1000;
  /* TODO make it reasonable */

  priority_queue_init(&ret, population_size, 
                      sizeof (ai_evol_ELEMENT),
                      &delete_ai_element,
                      &copy_ai_element);

  for (i = 0; i < redundancy; ++i)
  {
    for (j = 0; j < SIZE_OF_BASE_PARAMS; ++j)
    {
      hrir_ai_ELEMENT base_element 
        = {original_image, basic_params[j] };
      ai_evol_ELEMENT element;

      element.rank = INT_MIN;
      element.creation_phase = 0;
      element.element = &base_element;
      element.method_id = -1;
      element.creation_phase = 0;

      // copy the element
      priority_queue_insert(&ret, &element, INT_MIN);
    }
  }
  return ret;
}

/*********************************************************/

static int
calc_rank(const ai_evol_ELEMENT* current_item)
{
  hrir_ai_ELEMENT* current_element = 
    (hrir_ai_ELEMENT*)current_item->element;
  image_reconstruct_PARAMETERS params = current_element->param;
  unsigned mse = 0; /* mean squer error */
  double psnr = 0;
  int rank;
  DEBUG_UTIL_TRACE(1, "Calc rank of:\n", 0);
  DEBUG_UTIL_TRACE_ELEMENT(1, &params,
                           image_reconstruct_trace_parameter);
  image_reconstruct_ERROR_CODE error = 
    image_reconstruct_calculate_mse(current_element->original_image,
                                    &params, 
                                    NULL,
                                    &mse,
                                    &psnr);
  
  assert(error == IMAGE_RECONSTRUCT_OK);
  /* assigne penality due to age of the item */
  rank = psnr * 10;

  DEBUG_UTIL_TRACE(1, "Rank:%d\n", rank);

  return rank;
}

/*********************************************************/

ai_evol_STATE
hrir_ai_iterate(const ai_evol_STATE* phase)
{
  return ai_evol_iterate(phase);
}

/*********************************************************/

static void*
copy_ai_element(void* dest, const void *element, size_t size)
{
  ai_evol_ELEMENT* ai_dest = (ai_evol_ELEMENT*)dest;
  hrir_ai_ELEMENT* hrir_dest;
  const ai_evol_ELEMENT* ai_element = (const ai_evol_ELEMENT*)element;
  const hrir_ai_ELEMENT* hrir_element = 
    (const hrir_ai_ELEMENT*)ai_element->element;

  ai_dest->element = malloc(sizeof(hrir_ai_ELEMENT));
  assert(ai_dest->element != NULL);
  memset(ai_dest->element, 0, sizeof(hrir_ai_ELEMENT)); 

  hrir_dest = (hrir_ai_ELEMENT*)ai_dest->element;

  IGNORE_UNUSED_WARIABLE(size);
  hrir_dest->original_image = hrir_element->original_image;

  hrir_dest->param = hrir_element->param;
  ai_dest->rank = ai_element->rank;
  ai_dest->method_id = ai_element->method_id;
  ai_dest->creation_phase = ai_element->creation_phase;
  return hrir_dest;
}


/*********************************************************/

static void
delete_ai_element(void* element)
{
  ai_evol_ELEMENT* ai_element = (ai_evol_ELEMENT*)element;
  hrir_ai_ELEMENT* hrir_element = (hrir_ai_ELEMENT*)ai_element->element;
  free(hrir_element);
  free(ai_element);
}

