#include "../header/image_amplifier.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <image_filter.h>
#include <gaussian_filter.h>
#include <median_filter.h>
#include <non_maxima.h>

#define COORD(img, i, j) img.content[(i * img.sizeX) + j]

#ifndef MAX
#define MAX_DEF
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif /* MAX */

#ifndef MIN
#define MIN_DEF
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif /* MIN */

/****************************************************/

static image_amplifier_ERROR_CODE 
preprocess_image(const image_filter_IMG* input,
                 const image_amplifier_OPTIONS* options,
                 image_filter_FILTER_GRID preprocessed_img);

/****************************************************/

static void
use_non_maxima(const image_filter_IMG* input,
               const non_maxima_GRADIENT_MASK mask,
               image_filter_FILTER_GRID out);

/****************************************************/

image_amplifier_ERROR_CODE
image_amplifier_details_up(const image_filter_IMG* input,
                           const image_amplifier_OPTIONS* options,
                           image_filter_IMG* out)
{
  image_amplifier_ERROR_CODE ret = IMAGE_AMPLIFIER_OK;
  image_filter_FILTER_GRID result;

  result = malloc(sizeof(image_filter_MASK_DATA) * input->width * input->height);
  assert(result != NULL);
  memset(result, 0, sizeof(image_filter_MASK_DATA) * input->width * input->height); 

  if ((ret = preprocess_image(input, options, result)))
  {
  }
  else
  {
    unsigned i, diff;
    for (i = 0; i < input->width * input->height; ++i)
    {
      diff = input->content[i] - result[i];
      result[i] = input->content[i] + diff;
    }
    options->scale(result, input, out);
  }
  free(result);
  return ret;
}

/****************************************************/

void 
image_amplifier_scale(const image_filter_FILTER_GRID input,
                      const image_filter_IMG* original,
                      image_filter_IMG* out)
{
  int max = input[0], min = input[0];
  unsigned i;
  int diff;
  double ratio;
  assert(original);

  for (i = 0; i < out->width * out->height; ++i)
  {
    if (max < input[i])
      max = input[i];
    if (min > input[i])
      min = input[i];
  }
  diff = max - min;
  ratio = 255 / (double)diff;

  for (i = 0; i < out->width * out->height; ++i)
  {
    out->content[i] = (input[i] - min) * ratio;
  }
}

/****************************************************/

void
image_amplifier_scale_to_origin(const image_filter_FILTER_GRID input,
                                     const image_filter_IMG* original,
                                     image_filter_IMG* out)
{
  int max = input[0], min = input[0];
  unsigned i = 0;
  int diff = 0, original_diff = 0;
  double ratio = 0.;

  for (i = 0; i < out->width * out->height; ++i)
  {
    if (max < input[i])
      max = input[i];
    if (min > input[i])
      min = input[i];
  }
  diff = max - min;
  for (i = 0; i < out->width * out->height; ++i)
  {
    if (max < original->content[i])
      max = original->content[i];
    if (min > original->content[i])
      min = original->content[i];
  }
  original_diff = max - min;
  ratio = original_diff / (double)diff;

  for (i = 0; i < out->width * out->height; ++i)
  {
    out->content[i] = min + (input[i] - min) * ratio;
  }
}

/****************************************************/

void
image_amplifier_cut_scale(const image_filter_FILTER_GRID input,
                               const image_filter_IMG* original,
                               image_filter_IMG* out)
{
  unsigned i = 0;
  assert(original);
  for (i = 0; i < out->width * out->height; ++i)
  {
    out->content[i] = MAX(MIN(input[i], 255), 0);
  }
}

/****************************************************/

void
image_amplifier_avg_scale(const image_filter_FILTER_GRID input,
                          const image_filter_IMG* original,
                          image_filter_IMG* out)
{
  unsigned i;
  for (i = 0; i < out->width * out->height; ++i)
  {
    out->content[i] = MAX(MIN((input[i] + original->content[i]) / 2,
                              255),
                          0);
  }
  
}
/****************************************************/

static void
create_filter(const image_amplifier_OPTIONS* opt,
              image_filter_FILTER* filter)
{
  switch (opt->type)
  {
    case IMAGE_AMPLIFIER_GAUSSIAN:
      gaussian_filter_set_sigma(opt->params.gaussian.sigma);
      image_filter_create_filter_by_function(opt->filter_size,
                                             &gaussian_filter_calc,
                                             filter);
      break;
    case IMAGE_AMPLIFIER_MEDIAN:
      image_filter_create_filter_function(opt->filter_size,
                                          &median_filter_apply_filter,
                                          filter);
  }
}

/****************************************************/

static image_amplifier_ERROR_CODE 
preprocess_image(const image_filter_IMG* input,
                 const image_amplifier_OPTIONS* options,
                 image_filter_FILTER_GRID preprocessed_img)
{
  image_amplifier_ERROR_CODE ret = IMAGE_AMPLIFIER_OK;

  if (options->method == IMAGE_AMPLIFIER_APPLY_FILTER)
  {
    image_filter_ERROR_CODE filter_error;
    image_filter_FILTER filter = {0}; 

    create_filter(options,
                  &filter);
    if ((filter_error = image_filter_apply_filter(input,
                                                  &filter,
                                                  preprocessed_img) != IMAGE_FILTER_OK))
    {
      ret = IMAGE_AMPLIFIER_FILTER_ERROR;
    }
  }
  else if (options->method == IMAGE_AMPLIFIER_NON_MAXIMA)
  {
    use_non_maxima(input,
                   options->params.non_maxima.mask,
                   preprocessed_img);
  }

  return ret;
}

/****************************************************/

static void
use_non_maxima(const image_filter_IMG* in,
               const non_maxima_GRADIENT_MASK mask,
               image_filter_FILTER_GRID out)
{
  non_maxima_DATA_GRID input = in->content;
  non_maxima_DATA_GRID res = NULL;
  unsigned i;
  
  non_maxima_init_data_grid(&res, in->width * in->height);
  
  non_maxima_process_image(input, 
                           mask,
                           in->width,
                           in->height,
                           res);
  for (i = 0; i < in->width * in->height; ++i)
  {
    out[i] = (input[i] + res[i]) / 2;
  }
  non_maxima_destroy_data_grid(res);

}
#ifdef MAX_DEF
#undef MAX_DEF
#undef MAX
#endif /* MAX_DEF */

#ifdef MIN_DEF
#undef MIN_DEF
#undef MIN
#endif /* MIN_DEF */

#undef COORD

