#include "../header/smart_hrir.h"

#include "../header/hrir_ai.h"
#include "../header/compile_uti.h"

#include <ai_evol/priority_queue.h>
#include <hrir/image_reconstruct.h>
#include <hrir/image_filter.h>
#include <hrir/dumper.h>
#include <debug_util/debug.h>

#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define RANK_OF_NODE(node) (((ai_evol_ELEMENT*)node->element)->rank)
#define MIN(x, y) ((x) < (y) ? (x) : (y))

static void
calc_avg(image_filter_IMG* result,
         list_LIST* images);

static void
image_destroy_wrapper(void* img);

static void*
image_copy_wrapper(void* dest,
                         const void* element, size_t size);

image_filter_IMG
smart_hrir_start_algorithm(const image_filter_IMG* input,
                           smart_hrir_SETTINGS* settings,
                           unsigned* reached_iteration,
                           int* reached_rank)
{
  ai_evol_STATE start_state = 
    hrir_ai_create_init_state(input,
                              settings->keep_counter,
                              settings->iteration_per_level,
                              settings->redundancy);
  ai_evol_STATE best_state;
  image_filter_IMG best_image;
  list_LIST best_images;
  int best_rank = INT_MIN;
  unsigned i = 0;
  DEBUG_UTIL_TRACE(0, "reconstruct with: \n"
                   "  keep counter:        %u\n"
                   "  redundancy:          %u\n"
                   "  iteration limit:     %u\n"
                   "  iteration per level: %u\n"
                   "  target rank:         %u\n",
                   settings->keep_counter,
                   settings->redundancy,
                   settings->iteration_limit,
                   settings->iteration_per_level,
                   settings->target_rank);

  best_state = ai_evol_start(&start_state,
                             settings->iteration_limit,
                             settings->target_rank);
  /* create list of best images */
  {
    DEBUG_UTIL_TRACE(0, "Create list of best images\n", 0);
    list_LIST bests = 
      priority_queue_to_list(&best_state.population);
    /* list of ai_evol_ELEMENTs */
    struct list_NODE* node = bests.first_element;
    best_rank = (node != NULL) ? RANK_OF_NODE(node)
                                   : INT_MIN;
    DEBUG_UTIL_TRACE(1, "best rank: %d\n", best_rank);

    list_init_list(&best_images, 
                   sizeof(image_filter_IMG),
                   &image_destroy_wrapper,
                   &image_copy_wrapper);

    while (node != NULL
           && RANK_OF_NODE(node) == best_rank)
    {
      DEBUG_UTIL_TRACE(1, "merge best images: %d\n", i);
      ai_evol_ELEMENT* best = node->element;

      image_reconstruct_PARAMETERS best_param =
        ((hrir_ai_ELEMENT*)best->element)->param;

      /* create image */
      image_filter_IMG img;
      image_reconstruct_ERROR_CODE res;
      image_filter_create_image(input->width * 2,
                                input->height * 2,
                                &img);
      DEBUG_UTIL_TRACE_ELEMENT(1, &best_param,
                               image_reconstruct_trace_parameter);
      /* calculate the result */
      res =
        image_reconstruct_from_lower_image(input,
                                           &best_param,
                                           &img);
      assert(res == IMAGE_RECONSTRUCT_OK);
      list_add_element(&best_images, &img);

      node = node->next;
      ++i;
    }
    list_destroy(&bests);
  }

  image_filter_create_image(input->width * 2,
                            input->height * 2,
                            &best_image);

  calc_avg(&best_image, &best_images);

  ai_evol_destroy_state(&best_state);
  ai_evol_destroy_state(
      &start_state);
  list_destroy(&best_images);

  if (reached_rank)
    *reached_rank = best_rank;
  if (reached_iteration)
    *reached_iteration = best_state.phase_counter;
  return best_image;
}

static void
calc_avg(image_filter_IMG* result,
         list_LIST* images)
{
  unsigned i = 0, j = 0;
  unsigned num_of_images = list_size(images);
  DEBUG_UTIL_TRACE(3, "Calculate AVG\n", 0);
  DEBUG_UTIL_TRACE(3, "num of images: %d\n", num_of_images);

  for (i = 0; i < result->height; ++i)
  {
    for (j = 0; j < result->width; ++j)
    {
      unsigned val = 0;
      struct list_NODE* node = images->first_element;
      while (node != NULL)
      {
        image_filter_IMG* img = node->element;
        val += img->content[i * result->width + j];
        node = node->next;
      }

      result->content[i * result->width + j] 
        = MIN(255, val / num_of_images); 
    }
  }
}

static void
image_destroy_wrapper(void* img)
{
  image_filter_destroy_image(img);
}

static void*
image_copy_wrapper(void* dest,
                         const void* element, size_t size)
{
  IGNORE_UNUSED_WARIABLE(size);
  image_filter_copy_to(dest, element);
  return dest;
}


#undef RANK_OF_NODE
#undef MIN
