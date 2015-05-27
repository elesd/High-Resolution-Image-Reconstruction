/**
* @file image_reconstruct.h
* Functions for image reconstruction.
* Reconstruction consist of 2 main steps reconstruction and reconstraction.
*/
#ifndef IMAGE_RECONSTRUCT_H
#define IMAGE_RECONSTRUCT_H

#include "image_filter.h"
#include <debug_util/debug.h>
#include <math.h>

/** @nodoc */
#define IMAGE_RECONSTRUCT_OK 0

/** @nodoc */
#define IMAGE_RECONSTRUCT_APPROX_ERROR -8
/** @nodoc */
#define IMAGE_RECONSTRUCT_INVALID_FILTER -9
/** @nodoc */
#define IMAGE_RECONSTRUCT_INVALID_SCALE -10
/** @nodoc */
#define IMAGE_RECONSTRUCT_PREPARATION_ERROR -10
/** @nodoc */
#define IMAGE_RECONSTRUCT_MEM_ERROR -20

#ifndef IMAGE_RECONSTRUCT_MAX_PIXEL_VALUE 
/**
* @brief Maximum possible value of a pixel.
*/
#define IMAGE_RECONSTRUCT_MAX_PIXEL_VALUE 255
#endif

/**
* @brief Function to calculate distance between two point.
* @details It is used for psnr and mse calculation. Due to 
*          performance reason it uses abs like first norm, but
*          it could be modified to other functionality like squer.
*          If you compile the library with IMAGE_RECONSTRUCT_USE_REAL_SQUER
*          compiler switch than it force to use this definition.
* @see #image_reconstruct_calculate_mse
*/
#define IMAGE_RECONSTRUCT_DIFF_FUNC(x, y) abs((x) - (y))
#ifdef IMAGE_RECONSTRUCT_USE_REAL_SQUER
#  define IMAGE_RECONSTRUCT_DIFF_FUNC(x, y) (sqrt(((x) - (y)) * ((x) - (y))))
#endif

/******************************************************************************/
/** @nodoc */
typedef int image_reconstruct_ERROR_CODE;

/******************************************************************************/

/** The enumeration of known edge detection during non maxima method.*/
typedef enum
{
  /** Sobel mask */
  IMAGE_RECONSTRUCT_SOBEL,
  /** Prewit mask */
  IMAGE_RECONSTRUCT_PREWIT
} image_reconstruct_NON_MAXIMA_FILTER_TYPE;

/******************************************************************************/

/** The enumeration of known edge scale method*/
typedef enum
{
  /** Scale the preprocessed image like the original */
  IMAGE_RECONSTRUCT_SCALE_TO_ORIGIN,
  /** Scale the preprocessed image to the whole boundary [0,255] */
  IMAGE_RECONSTRUCT_SCALE_UP,
  /** Cut the preprocessed image in the boundary */
  IMAGE_RECONSTRUCT_SCALE_CUT,
  /** Get the preprocessed and the original image avarage */
  IMAGE_RECONSTRUCT_SCALE_AVG,
  /** Number of known scale method. */
  IMAGE_RECONSTRUCT_NUM_OF_SCALE_METHOD
} image_reconstruct_SCALE_METHOD;

/******************************************************************************/

/**
* @brief the type of different preprocessor methods
*/
typedef enum
{
  /** In that case the edges will be increased by non maxima edge detection */
  IMAGE_RECONSTRUCT_NON_MAXIMA,
  /** In that case the edges will be increased by Median filter
  * @see #image_amplifier_details_up
  */
  IMAGE_RECONSTRUCT_MEDIAN,

  /** In that case the edges will be increased by Gaussian filter
  * @see #image_amplifier_details_up
  */
  IMAGE_RECONSTRUCT_GAUSSIAN
} image_reconstruct_PREPROCESS_TYPE;

/******************************************************************************/

/**
* @brief Parameter for image preprocessing
*/
typedef struct
{
  /** Parameters for the filter */
  union
  {
    /** Gaussian filter param */
    double gaussian_sigma;
    /** non maxima filter type */
    image_reconstruct_NON_MAXIMA_FILTER_TYPE non_maxima_type;
  } params;

  /** The type of the preprocessing */
  image_reconstruct_PREPROCESS_TYPE type;

  /** The size of the applied filter */
  unsigned size;

  /** The way of the scaling method */
  image_reconstruct_SCALE_METHOD scaling;

} image_reconstruct_PARAMETERS;
 
/******************************************************************************/

/**
  * @brief Calculates the error during the reconstruction.
  * @details This function first call up the #image_reconstruct_from_lower_image 
  *          function. After creates the Haar-transform of the approximation.
  *          On this image - which has a same size as the original one -
  *          calculates something similar like MSE (mean squered error). This function
  *          calculates not the second norm of this picture only the first, due
  *          to performance issues. The two norms - if we are looking the pictures
  *          as vector space - are equivalent, therefore it can be used to measure
  *          the error.
  *          The PSNR is calculated based on the modified mse value. It won't cause 
  *          problem due to the equivality.
  * @param original the original image
  * @param params the way of the intensity increasing
  * @param result Result image with double size
  * @param mse mean squered error
  * @param psnr Peak signal-to-noise ratio
  * @return The error code
  */
image_reconstruct_ERROR_CODE 
image_reconstruct_calculate_mse(const image_filter_IMG* original,
                                const image_reconstruct_PARAMETERS* params,
                                image_filter_IMG* result,
                                unsigned* mse,
                                double* psnr);

/******************************************************************************/

/**
  * @brief Create a double sized image from the original
  * @details First step the code increase the intensity of the details with 
  *          the given mehtod. Thereafter calculate the horizontal and vertical
  *          edges. With these two images calculates the diagonal edges. Finally
  *          with an inverse Haar transformation calculates the bigger image.
  * @param original the original image
  * @param params the way of the intensity increasing
  * @param result Result image with double size
  * @return The error code
  */
image_reconstruct_ERROR_CODE
image_reconstruct_from_lower_image(const image_filter_IMG* original,
                                   const image_reconstruct_PARAMETERS* params,
                                   image_filter_IMG* result);
/******************************************************************************/
/**
* Trace a given parameter to the buffer.
* It is usefull to use with the debug_util for trace.
* \param parameter: parameter to print out
* \param buffer: the parameter trace will be written into this buffer.
*/
void
image_reconstruct_trace_parameter(void* parameter,
                                  char buffer[DEBUG_UTIL_BUFFER_SIZE]);
#endif
