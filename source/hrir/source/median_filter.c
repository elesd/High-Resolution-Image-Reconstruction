#include "../header/median_filter.h"

#include <stdlib.h>
#include <assert.h>

#define EPSILON 100

static image_filter_IMG_DATA g_buffer[MEDIAN_FILTER_MAX_FILTER_SIZE
                                      * MEDIAN_FILTER_MAX_FILTER_SIZE];

static int buffer_sorter(const void* a, const void* b)
{
  return ((int)((*(const double*)a - *(const double*)b) * EPSILON)) / EPSILON;
}

static void
sort_buffer(const unsigned size)
{
  qsort(g_buffer, (size - 1) * (size - 1), sizeof(image_filter_IMG_DATA), buffer_sorter);
}

static double
median_of_buffer(const unsigned size)
{
  unsigned array_size = (size - 1) * (size - 1);
  return (g_buffer[array_size / 2] + g_buffer[array_size / 2]) / 2;
}

double
median_filter_apply_filter(const image_filter_IMG_DATA img_data,
                           const double x,
                           const double y,
                           const unsigned size)
{
  if ( (x + y) != (size - 1) * (size - 1))
  {
    assert((int)((y * size) + x) < MEDIAN_FILTER_MAX_FILTER_SIZE
                                   * MEDIAN_FILTER_MAX_FILTER_SIZE);
    g_buffer[(int)((y * size) + x)] = img_data;
    return 0.0;
  }
  else
  {
    sort_buffer(size);
    return median_of_buffer(size);
  }
}

#undef EPSILON
