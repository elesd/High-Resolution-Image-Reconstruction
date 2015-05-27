/**
* @file non_maxima.h
* Non-maxima filter.
* Not just looks for edge detectation, but also increase the edge lines.
*/
#ifndef NON_MAXIMA
#define NON_MAXIMA

/** @nodoc */
#define NON_MAXIMA_WINDOW_SIZE 3

/** @nodoc */
#define NON_MAXIMA_PREWITT_GRADIENT_MASK {-1, 0, 1,\
                                          -1, 0, 1,\
                                          -1, 0, 1}

/** @nodoc */
#define NON_MAXIMA_SOBEL_GRADIENT_MASK {-1, 0, 1,\
                                        -2, 0, 2,\
                                        -1, 0, 1}
/*************************************************************************/
/** @nodoc */
typedef unsigned char* non_maxima_DATA_GRID;

/*************************************************************************/
/** @nodoc */
typedef int* non_maxima_GRAD_GRID;

/*************************************************************************/
/** @nodoc */
typedef	int non_maxima_GRADIENT_MASK[NON_MAXIMA_WINDOW_SIZE * 3];

/************************* FUNCTIONS *************************************/
/**
* @brief Initialization of a given data grid.
* @param data data grid to initialize
* @param size of the data grid.
*/
void
non_maxima_init_data_grid
(
  non_maxima_DATA_GRID* data,
	unsigned int size
);

/*************************************************************************/
/**
* @brief Initialize a gradient grid.
* @param data the given grid
* @param size the size of the new grid
*/
void
non_maxima_init_grad_grid
(
  non_maxima_GRAD_GRID* data,
	unsigned int size
);

/*************************************************************************/
/**
* @brief destroy the given data grid
* @param data the given data.
*/
void
non_maxima_destroy_data_grid
(
  non_maxima_DATA_GRID data
);

/*************************************************************************/
/**
* @brief destroy the given gradient grid
* @param data the given data.
*/
void
non_maxima_destroy_grad_grid
(
  non_maxima_GRAD_GRID data
);

/*************************************************************************/
/**
* @brief Execute the algorithm on the given input image.
* @param input the input image
* @param mask the mask to use
* @param size_x the size of the given image
* @param size_y the size of the given image
* @param output the output image.
*/
void
non_maxima_process_image
(
  const non_maxima_DATA_GRID input,
	const non_maxima_GRADIENT_MASK mask,
	const unsigned int size_x,
	const unsigned int size_y,
	non_maxima_DATA_GRID output
);

/*************************************************************************/
/**
* @brief Execute the algorithm on the given input image.
* This function keeps the gradient map.
* @param input the input image
* @param mask the mask to use
* @param size_x the size of the given image
* @param size_y the size of the given image
* @param output the output image.
* @param grad_mag_map the gradiant map of the image.
*/
void
non_maxima_process_image_with_grad_map
(
  const non_maxima_DATA_GRID input,
	const non_maxima_GRADIENT_MASK mask,
	const unsigned int size_x,
	const unsigned int size_y,
	non_maxima_DATA_GRID output,
	non_maxima_GRAD_GRID grad_mag_map
);

#endif

