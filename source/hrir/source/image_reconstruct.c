#include "image_reconstruct.h"

#include <debug_util/debug.h>
#include <stdlib.h>
#include <image_amplifier.h>
#include <haar_transformation.h>
#include <non_maxima.h>
#include <dumper.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#ifndef MAX
#  define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#  define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#define PREWITT_ROW_MASK {-0.33, 0.0, 0.33,\
                          -0.33, 0.0, 0.33,\
                          -0.33, 0.0, 0.33}

#define PREWITT_COL_MASK {0.33, 0.33, 0.33,\
                          0.00, 0.00, 0.00,\
                          -0.33, -0.33, -0.33}


static image_reconstruct_ERROR_CODE
prepare_image(const image_filter_IMG* original,
              const image_reconstruct_PARAMETERS* params,
              image_filter_IMG* out);

/******************************************************************************/

static image_reconstruct_ERROR_CODE
apply_filter(const image_filter_IMG* original,
             image_filter_FILTER* filter,
             image_filter_IMG* out);

/******************************************************************************/

static void
calculate_sum(const image_filter_IMG* a,
              const image_filter_IMG* b,
              const image_filter_IMG* c,
              image_filter_IMG* out);

/******************************************************************************/

static image_reconstruct_ERROR_CODE
do_reconstruction(const image_filter_IMG* original,
                  const image_reconstruct_PARAMETERS* params,
                  image_filter_IMG* result);

/******************************************************************************/

image_reconstruct_ERROR_CODE 
image_reconstruct_calculate_mse(const image_filter_IMG* original,
                                const image_reconstruct_PARAMETERS* params,
                                image_filter_IMG* result,
                                unsigned* mse,
                                double* psnr)
{
  image_filter_IMG res = {0}; 
  image_filter_IMG* work_img = result ? result : &res;

  image_reconstruct_ERROR_CODE er;
  image_filter_create_image(original->width * 2,
                            original->height * 2,
                            &res);
  er = 
    image_reconstruct_from_lower_image(original,
                                       params,
                                       work_img);
  assert(er == IMAGE_RECONSTRUCT_OK);
  {
    unsigned long error = 0;
    unsigned i = 0, j = 0;
    double factor = 1/(double)(original->width * original->height);

    image_filter_IMG avg = {0};
    image_filter_IMG row = {0};
    image_filter_IMG col = {0};
    image_filter_IMG diag = {0};
    haar_transformation_DATA_SOURCE source;
    image_filter_create_image(original->width,
                              original->height,
                              &avg);
    image_filter_create_image(original->width,
                              original->height,
                              &row);
    image_filter_create_image(original->width,
                              original->height,
                              &col);
    image_filter_create_image(original->width,
                              original->height,
                              &diag);
    
    source.width = work_img->width;
    source.height = work_img->height;  
    source.original_image = work_img->content;
    source.avg_image = avg.content;
    source.vertical_edges = col.content;
    source.horizontal_edges = row.content;
    source.diagonal_edges = diag.content;

    haar_transformation_transform(source);

    for (i = 0; i < original->height; ++i)
    {
      for (j = 0; j < original->width; ++j)
      {
        error += 
          IMAGE_RECONSTRUCT_DIFF_FUNC(
              avg.content[i * original->width + j],
              original->content[i * original->width + j]);
      }
    }
    (*mse) = factor * error;
    (*psnr) = 
      10 
      * log10(IMAGE_RECONSTRUCT_MAX_PIXEL_VALUE 
              * IMAGE_RECONSTRUCT_MAX_PIXEL_VALUE / (double)(*mse));
    er = IMAGE_RECONSTRUCT_OK;
    image_filter_destroy_image(&avg);
    image_filter_destroy_image(&row);
    image_filter_destroy_image(&col);
    image_filter_destroy_image(&diag);
  }
  image_filter_destroy_image(&res);
  return er;
}

/******************************************************************************/

image_reconstruct_ERROR_CODE
image_reconstruct_from_lower_image(const image_filter_IMG* original,
                                   const image_reconstruct_PARAMETERS* params,
                                   image_filter_IMG* result)
{
  image_reconstruct_ERROR_CODE ret;
  ret = do_reconstruction(original,
                          params,
                          result);
  assert(ret == IMAGE_RECONSTRUCT_OK);
  
  return ret;
}

/******************************************************************************/

static image_reconstruct_ERROR_CODE
do_reconstruction(const image_filter_IMG* original,
                  const image_reconstruct_PARAMETERS* params,
                  image_filter_IMG* result)
{
  image_reconstruct_ERROR_CODE ret = IMAGE_RECONSTRUCT_OK;
  image_filter_FILTER row_filter = {0};
  image_filter_FILTER col_filter = {0};
  image_filter_IMG approx_row = {0};
  image_filter_IMG approx_col = {0};
  image_filter_IMG approx_diag = {0};
  image_filter_IMG tmp = {0};
  double row_mask[] = PREWITT_ROW_MASK;
  double col_mask[] = PREWITT_COL_MASK;


  image_filter_create_filter_by_mask(3,
                                     row_mask,
                                     &row_filter);
  image_filter_create_filter_by_mask(3,
                                     col_mask,
                                     &col_filter);
  image_filter_create_image(original->width,
                            original->height,
                            &approx_row);
  image_filter_create_image(original->width,
                            original->height,
                            &tmp);
  image_filter_create_image(original->width,
                            original->height,
                            &approx_col);
  image_filter_create_image(original->width,
                            original->height,
                            &approx_diag);
  if ((ret = prepare_image(original, params, &tmp))
             != IMAGE_AMPLIFIER_OK)
  {}
  else if ((ret = apply_filter(&tmp,
                               &row_filter,
                               &approx_row)) != IMAGE_RECONSTRUCT_OK)
  {}
  else if ((ret = apply_filter(&tmp,
                               &col_filter,
                               &approx_col)) != IMAGE_RECONSTRUCT_OK)
  {}

  if (ret == IMAGE_RECONSTRUCT_OK)
  {
    haar_transformation_DATA_SOURCE data;

    calculate_sum(&approx_col,
                  &approx_row,
                  NULL,
                  &approx_diag);
 
    data.width = original->width;
    data.height = original->height;
    data.original_image = result->content;
    data.avg_image = tmp.content;
    data.vertical_edges = approx_col.content;
    data.horizontal_edges = approx_row.content;
    data.diagonal_edges = approx_diag.content;

  /*  DUMPER_TRACE_IMAGE(data.avg_image, data.width, data.height);
    DUMPER_TRACE_IMAGE(data.vertical_edges, data.width, data.height);
    DUMPER_TRACE_IMAGE(data.horizontal_edges, data.width, data.height);
    DUMPER_TRACE_IMAGE(data.diagonal_edges, data.width, data.height);
    DUMPER_TRACE_IMAGE(tmp.content, data.width, data.height); */
    data.width *= 2;
    data.height *= 2;
    haar_transformation_inverse_transformation(data);
 /*   DUMPER_TRACE_IMAGE(data.original_image, data.width, data.height); */
  }

  image_filter_destroy_image(&approx_diag);
  image_filter_destroy_image(&tmp);
  image_filter_destroy_image(&approx_col);
  image_filter_destroy_image(&approx_row);
  image_filter_destroy_filter(&row_filter);
  image_filter_destroy_filter(&col_filter);

  return ret;
}

/******************************************************************************/

static image_reconstruct_ERROR_CODE
prepare_image(const image_filter_IMG* original,
              const image_reconstruct_PARAMETERS* params,
              image_filter_IMG* out)
{
  non_maxima_GRADIENT_MASK mask = NON_MAXIMA_PREWITT_GRADIENT_MASK;
  image_amplifier_OPTIONS opt;
  switch (params->type)
  {
    case IMAGE_RECONSTRUCT_GAUSSIAN:
      opt.params.gaussian.sigma = params->params.gaussian_sigma;
      opt.type = IMAGE_AMPLIFIER_GAUSSIAN;
      opt.method = IMAGE_AMPLIFIER_APPLY_FILTER;
      break;
    case IMAGE_RECONSTRUCT_MEDIAN:
      opt.type = IMAGE_AMPLIFIER_MEDIAN;
      opt.method = IMAGE_AMPLIFIER_APPLY_FILTER;
      break;
    case IMAGE_RECONSTRUCT_NON_MAXIMA:
      opt.method = IMAGE_AMPLIFIER_NON_MAXIMA;
      switch (params->params.non_maxima_type)
      {
        case IMAGE_RECONSTRUCT_SOBEL:
          memcpy(opt.params.non_maxima.mask,
                 mask,
                 sizeof(non_maxima_GRADIENT_MASK));
          break;
        case IMAGE_RECONSTRUCT_PREWIT:
          memcpy(opt.params.non_maxima.mask,
                 mask,
                 sizeof(non_maxima_GRADIENT_MASK));
          break;
        default:
          /* ERROR*/
          return IMAGE_RECONSTRUCT_INVALID_FILTER;
      }
      break;
    default:
      return IMAGE_RECONSTRUCT_INVALID_FILTER;
  }
  opt.filter_size = params->size;
  switch (params->scaling)
  {
    case IMAGE_RECONSTRUCT_SCALE_UP:
      opt.scale = image_amplifier_scale;
      break;
    case IMAGE_RECONSTRUCT_SCALE_TO_ORIGIN:
      opt.scale = image_amplifier_scale_to_origin;
      break;
    case IMAGE_RECONSTRUCT_SCALE_AVG:
      opt.scale = image_amplifier_avg_scale;
      break;
    case IMAGE_RECONSTRUCT_SCALE_CUT:
      opt.scale = image_amplifier_cut_scale;
      break;
    default:
          /* ERROR*/
      return IMAGE_RECONSTRUCT_INVALID_SCALE;
  }

  if (image_amplifier_details_up(original,
                                 &opt,
                                 out) != IMAGE_AMPLIFIER_OK)
    return IMAGE_RECONSTRUCT_PREPARATION_ERROR;


  return IMAGE_AMPLIFIER_OK;
}

/******************************************************************************/

static image_reconstruct_ERROR_CODE
apply_filter(const image_filter_IMG* original,
             image_filter_FILTER* filter,
             image_filter_IMG* out)
{
  image_filter_ERROR_CODE filter_error;
  image_filter_FILTER_GRID result;
  result = malloc(sizeof(image_filter_MASK_DATA) * original->width * original->height);
  assert(result != NULL);
  memset(result, 0, sizeof(image_filter_MASK_DATA) * original->width * original->height);

  filter_error = image_filter_apply_filter(original, filter, result);
  if (filter_error != IMAGE_FILTER_OK)
    return IMAGE_RECONSTRUCT_APPROX_ERROR;


  image_amplifier_scale_to_origin(result, original, out);
  free(result);
  return IMAGE_RECONSTRUCT_OK;
}

/******************************************************************************/

static void
calculate_sum(const image_filter_IMG* a,
              const image_filter_IMG* b,
              const image_filter_IMG* c,
              image_filter_IMG* out)
{
  image_filter_FILTER_GRID result;
  unsigned i;
  result = malloc(sizeof(image_filter_MASK_DATA) * a->width * a->height);
  assert(result != NULL);
  memset(result, 0, sizeof(image_filter_MASK_DATA) * a->width * a->height); 
  
  for (i = 0; i < a->height * a->width; ++i)
  {
    result[i] = a->content[i] + b->content[i];
    if (c)
      result[i] += c->content[i];
  }
  image_amplifier_scale(result, a, out);
  free(result);
}

/******************************************************************************/

void
image_reconstruct_trace_parameter(void* parameter,
                                  char buffer[DEBUG_UTIL_BUFFER_SIZE])
{
  static const char* preprocess_type_to_str[] = 
    { 
      "Non maxima filter", 
      "Median filter",
      "Gaussian filter"
    };
  static const char* scale_method_to_str[] =
    {
      "Scale to origin",
      "Scale up",
      "Scale cut",
      "Scale avg"
    };
  static const char* non_maxima_filter_type_to_str[] =
    {
      "Sobel mask",
      "Prewit mask"
    };
  int offset = 0;
  image_reconstruct_PARAMETERS* params = 
    (image_reconstruct_PARAMETERS*)parameter;

  offset = snprintf(buffer, DEBUG_UTIL_BUFFER_SIZE, 
                    "Parameter: \n"
                    "  size of applied filter: %u\n"
                    "  type: %s\n"
                    "  scaling method: %s\n",
                    params->size,
                    preprocess_type_to_str[params->type],
                    scale_method_to_str[params->scaling]);
  if (params->type == IMAGE_RECONSTRUCT_NON_MAXIMA)
  {
    snprintf(buffer + offset, DEBUG_UTIL_BUFFER_SIZE - offset,
             "  Applied mask: %s\n",
             non_maxima_filter_type_to_str[params->params.non_maxima_type]);
  }
  else if (params->type == IMAGE_RECONSTRUCT_GAUSSIAN)
  {
    snprintf(buffer + offset, DEBUG_UTIL_BUFFER_SIZE - offset,
             "  Gaussian filter value %f\n",
             params->params.gaussian_sigma);
  }
  else
  {
    snprintf(buffer + offset, DEBUG_UTIL_BUFFER_SIZE - offset,
             "  Median buffer is in action\n");
  }
}
