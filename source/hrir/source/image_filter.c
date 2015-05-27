#include "../header/image_filter.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRANSFORM_COORD_X(x, size) ((x) - (size - 1) / 2.0)
#define TRANSFORM_COORD_Y(y, size) (-(y) + (size - 1) / 2.0)
#define COORD_XY(x, y, size) ((x) + (y) * size)

#define IMG_XY(img, x, y) (img->content[COORD_XY(x, y, img->width)])

/****************************************************/
static image_filter_ERROR_CODE
check_filter_type(const image_filter_FILTER* filter)
{
  if (filter->size % 2 != 1
      || filter->size == 0)
    return IMAGE_FILTER_FILTER_ERROR;

  return IMAGE_FILTER_OK;
}

/****************************************************/

image_filter_ERROR_CODE
image_filter_apply_filter(const image_filter_IMG* img,
                          const image_filter_FILTER* filter,
                          image_filter_FILTER_GRID out)
{
	int window_rad = filter->size / 2;
	unsigned int x, y;
  image_filter_ERROR_CODE ret;

  if ((ret = check_filter_type(filter)) != IMAGE_FILTER_OK)
    return ret;

	for (y = window_rad; y < img->height - window_rad; ++y)
		for (x = window_rad; x < img->width - window_rad; ++x)
		{
			int dx, dy;
			int sum = 0;

				/* Masking */
			for (dy = - window_rad; dy <= window_rad; ++dy)
			{
				for (dx = - window_rad; dx <= window_rad; ++dx)
				{
					sum += filter->mode == MASK ?
                   IMG_XY(img, x + dx, y + dy)
                   * filter->filter.mask[COORD_XY(window_rad + dx,
                                                  window_rad + dy,
                                                  filter->size)]
                 :
                   filter->filter.function(IMG_XY(img, x + dx, y + dy),
                                           window_rad + dx,
                                           window_rad + dy,
                                           filter->size);
  /*        printf("%d,%d: %d, [%d]\n", dx, dy, IMG_XY(img, x + dx, y + dy), sum); */
				}
			}

			out[COORD_XY(x, y, img->width)] = sum;
		}

  return IMAGE_FILTER_OK;
}

/****************************************************/

void
image_filter_create_image(const unsigned width,
                          const unsigned height,
                          image_filter_IMG* out)
{
  out->width = width;
  out->height = height;
  out->content = malloc(sizeof(image_filter_IMG_DATA) * width * height);
  assert(out->content != NULL);
  memset(out->content, 0, sizeof(image_filter_IMG_DATA) * width * height);
}

/****************************************************/

void
image_filter_create_filter_by_mask(const unsigned size,
                                   image_filter_MASK_GRID mask,
                                   image_filter_FILTER* out)
{
  out->size = size;

  out->filter.mask = malloc(sizeof(image_filter_MASK_DATA) * size * size);
  assert(out->filter.mask != NULL);
  memset(out->filter.mask, 0, sizeof(image_filter_IMG_DATA) * size * size);

  memcpy(out->filter.mask, mask, sizeof(image_filter_MASK_DATA) * size * size);

  out->mode = MASK;
}

/****************************************************/

void
image_filter_create_filter_by_function(const unsigned size,
                                       image_filter_MASK_FUNCTION mask,
                                       image_filter_FILTER* out)
{
  out->size = size;

  out->filter.mask = malloc(sizeof(image_filter_MASK_DATA) * size * size);
  assert(out->filter.mask != NULL);
  memset(out->filter.mask, 0, sizeof(image_filter_IMG_DATA) * size * size);

  {
    unsigned i, j;
    for (i = 0; i < size; ++i)
      for (j = 0; j < size; ++j)
      {
        out->filter.mask[COORD_XY(i, j, size)] = mask(i, j);
      }
  }

  out->mode = MASK;
}

/****************************************************/

void
image_filter_create_filter_function(const unsigned size,
                                    image_filter_FILTER_FUNCTION filter,
                                    image_filter_FILTER* out)
{
  out->size = size;
  out->filter.function = filter;
  out->mode = FUNCTION;
}

/****************************************************/

void
image_filter_destroy_filter(image_filter_FILTER* filter)
{
  if (filter->filter.mask != NULL)
    free(filter->filter.mask);
}

/****************************************************/

void
image_filter_destroy_image(image_filter_IMG* img)
{
  if (img->content != NULL)
    free(img->content);
}

/****************************************************/

image_filter_IMG
image_filter_copy(const image_filter_IMG* src)
{
  image_filter_IMG result;

  assert(src);
  image_filter_copy_to(&result, src);

  return result;
}

/****************************************************/

void
image_filter_copy_to(image_filter_IMG* dest, 
                     const image_filter_IMG* const element)
{
  assert(dest);
  assert(element);
  image_filter_create_image(element->width, element->height, dest);
  memcpy(dest->content, element->content, element->width * element->height 
                                       * sizeof(image_filter_IMG_DATA));
}
#undef TRANSFORM_COORD_X
#undef TRANSFORM_COORD_Y
#undef COORD_XY
#undef IMG_XY
