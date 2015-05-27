#include "../header/non_maxima.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "../header/percent_calculator.h"

#define MASK_XY(x,y) ((x) + (y) * NON_MAXIMA_WINDOW_SIZE)
#define DG_XY(x, y) ((x) + (y) * size_x)
#define SQR(x) ((x) * (x))
#define NORM(x) ((x) / abs (x))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define TRACE_INT(x) printf ("%s: %d (%x)\n", #x, x, x)
#define TRACE_FLOAT(x) printf ("%s: %f (%x)\n", #x, x, x)
#define TRACE_SHORT(x) printf ("%s: %hd (%x)\n", #x, x, x)
#define TRACE_STR(x) printf ("%s: %s\n", #x, x)
#define TRACE_CH(x) printf ("%s: %c (%x)\n", #x, x, x)
/*****************************************************************************/
static void
calc_grad
(
  const non_maxima_DATA_GRID input,
	const non_maxima_GRADIENT_MASK mask,
	const unsigned int size_x,
	const unsigned int size_y,
	non_maxima_GRAD_GRID diff_x,
	non_maxima_GRAD_GRID diff_y,
	non_maxima_GRAD_GRID grad_mag_map
)
{
	static int window_rad = NON_MAXIMA_WINDOW_SIZE / 2;
  unsigned int x = 0, y = 0;


	for (y = window_rad; y < size_y - window_rad; ++y)
		for (x = window_rad; x < size_x - window_rad; ++x)
		{
			int dx, dy;
			int sum_x = 0 , sum_y = 0;
	/*		printf("(%u, %u) [%u]\n", x, y, DG_XY(x,y));
			printf("%d %d %d\n"
					   "%d %d %d\n"
						 "%d %d %d\n", 
input[DG_XY(x - 1, y - 1)], input[DG_XY(x, y - 1)], input[DG_XY(x + 1, y - 1)],
input[DG_XY(x - 1, y)], input[DG_XY(x, y)], input[DG_XY(x + 1, y)],
input[DG_XY(x - 1, y + 1)], input[DG_XY(x, y + 1)], input[DG_XY(x + 1, y + 1)]);
			printf("mask:\n");

			printf("%d %d %d\n"
					   "%d %d %d\n"
						 "%d %d %d\n", 
mask[MASK_XY(0, 0)], mask[MASK_XY(1,0)], mask[MASK_XY(2, 0)],
mask[MASK_XY(0, 1)], mask[MASK_XY(1, 1)], mask[MASK_XY(2, 1)],
mask[MASK_XY(0, 2)], mask[MASK_XY(1, 2)], mask[MASK_XY(2, 2)]);*/
				/* Masking */
			for (dy = - window_rad; dy <= window_rad; ++dy)
			{
				for (dx = - window_rad; dx <= window_rad; ++dx)
				{
					sum_x += ((int)input[DG_XY(x + dx, y + dy)])
						       * mask[MASK_XY(window_rad + dx, window_rad + dy)];
					sum_y += ((int)input[DG_XY(x + dx, y + dy)])
						       * mask[MASK_XY(window_rad + dy, window_rad + dx)];
				}
			}
	/*		printf("sum x:%d\n", sum_x);
			printf("sum y:%d\n", sum_y);*/
			diff_x[DG_XY(x, y)] = (int) (sum_x);
			diff_y[DG_XY(x, y)] = (int) (sum_y);

			grad_mag_map[DG_XY(x, y)] = sqrt(SQR(diff_x[DG_XY(x,y)])
															     + SQR (diff_y[DG_XY(x, y)]));
		}
}

/*****************************************************************************/
static void
init_percent_calc
(
  non_maxima_GRAD_GRID map,
	unsigned int size,
	percent_calculator_CALCULATOR* calc
)
{	
	unsigned int i = 0;
	int min = map[0], max = map[0];
	for (; i < size; ++i)
	{
		min = min > map[i] ? map[i] : min;
		max = max < map[i] ? map[i] : max;
	}
	calc->min = min;
	calc->max = max;
}

/*****************************************************************************/

void
non_maxima_process_image_with_grad_map
(
  const non_maxima_DATA_GRID input,
	const non_maxima_GRADIENT_MASK mask,
	const unsigned int size_x,
	const unsigned int size_y,
	non_maxima_DATA_GRID output,
	non_maxima_GRAD_GRID grad_mag_map
)
{
	static int window_rad = NON_MAXIMA_WINDOW_SIZE / 2;
	non_maxima_GRAD_GRID diff_x;
	non_maxima_GRAD_GRID diff_y;

	non_maxima_init_grad_grid(&diff_x, size_x * size_y);
	non_maxima_init_grad_grid(&diff_y, size_x * size_y);

	calc_grad(input, mask, size_x, size_y,
						      diff_x,	diff_y,	grad_mag_map);
	{
    unsigned int x = 0, y = 0;
		percent_calculator_CALCULATOR calc;
    init_percent_calc(grad_mag_map, size_x * size_y, &calc);
		for (x = window_rad; x < size_x - window_rad; ++x)
		{
			for (y = window_rad; y < size_y - window_rad; ++y)
			{
				char dx = diff_x [DG_XY(x, y)] != 0 ? NORM (diff_x [DG_XY(x, y)])
					                                   : 0;
				char dy = diff_y [DG_XY(x, y)] != 0 ? NORM (diff_y [DG_XY(x, y)])
				                                    : 0;

				int A = grad_mag_map [DG_XY(x - dy, y - dx)];
				int B = grad_mag_map [DG_XY(x + dy, y + dx)];
				int C = grad_mag_map [DG_XY(x, y)];
	
				if (A > C || B > C)
					output [DG_XY (x, y)] = 0;
				else
					output [DG_XY (x, y)] = grad_mag_map [DG_XY(x, y)] > 255 ? 255 
						                                           : grad_mag_map[DG_XY(x,y)];
			}
		}
	}
	non_maxima_destroy_grad_grid(diff_x);
	non_maxima_destroy_grad_grid(diff_y);
}

/*****************************************************************************/

void
non_maxima_process_image
(
  const non_maxima_DATA_GRID input,
	const non_maxima_GRADIENT_MASK mask,
	const unsigned int size_x,
	const unsigned int size_y,
	non_maxima_DATA_GRID output
)
{
	non_maxima_GRAD_GRID grad_map = malloc(sizeof(int) * size_x * size_y);
  assert(grad_map != NULL);
  memset(grad_map, 0, sizeof(int) * size_x * size_y);

	non_maxima_process_image_with_grad_map(input, mask, size_x, size_y,
			                                         output, grad_map);
	free (grad_map);
}

/*************************************************************************/
void
non_maxima_init_data_grid
(
  non_maxima_DATA_GRID* data,
	unsigned int size
)
{
	*data = malloc (size * sizeof(unsigned char));
  assert(data != NULL);
	memset (*data, 0, sizeof (unsigned char) * size);
}

/*************************************************************************/
void
non_maxima_init_grad_grid
(
  non_maxima_GRAD_GRID* data,
	unsigned int size
)
{
	*data = malloc (size * sizeof(int));
  assert(data != NULL);
	memset (*data, 0, sizeof (int) * size);
}

/*************************************************************************/
void
non_maxima_destroy_data_grid
(
  non_maxima_DATA_GRID data
)
{
  if (data != NULL)	free(data);
}

/*************************************************************************/
void
non_maxima_destroy_grad_grid
(
  non_maxima_GRAD_GRID data
)
{
	if (data != NULL) free(data);
}

#undef MASK_XY
#undef DG_XY

#undef TRACE_INT
#undef TRACE_SHORT
#undef TRACE_STR
#undef TRACE_CH

