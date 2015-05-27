/**
* @file image_amplifier.h
* Functionalities for image modifications
*/
#ifndef IMAGE_AMPLIFIER_H
#define IMAGE_AMPLIFIER_H


#include "image_filter.h"
#include "non_maxima.h"

/** @nodoc */
#define IMAGE_AMPLIFIER_OK 0
/** @nodoc */
#define IMAGE_AMPLIFIER_FILTER_ERROR -10
/** @nodoc */
#define IMAGE_AMPLIFIER_NON_MAXIMA_ERROR -15
/** @nodoc */
#define IMAGE_AMPLIFIER_MEM_ERROR -20

/*************************************************************************/
/** @nodoc */
typedef int image_amplifier_ERROR_CODE;

/**
* @brief scale function pointer.
* @param input input grid.
* @param original pointer to the original image
* @param out The scaled image
*/
typedef void (*image_amplifier_SCALE_FUNCTION)(const image_filter_FILTER_GRID input,
                                               const image_filter_IMG* original,
                                               image_filter_IMG* out);

/**
 * @brief The enumeration of the known filters
 */
typedef enum
{
  IMAGE_AMPLIFIER_GAUSSIAN,
  IMAGE_AMPLIFIER_MEDIAN
} image_amplifier_FILTER_TYPE;

/**
* @brief The list of known preprocessor types
*/
typedef enum
{
  IMAGE_AMPLIFIER_APPLY_FILTER,
  IMAGE_AMPLIFIER_NON_MAXIMA
} image_amplifier_PROCESS_TYPE;

/**
  * @brief Structure to hold the parameter to the main functionality
  */
typedef struct
{
  /**
    * Filter parameter
    */
  union 
  {
    /**
      * @brief the gaussian params
      */
    struct 
    {
      double sigma;
    } gaussian;

    struct 
    {
      non_maxima_GRADIENT_MASK mask;
    } non_maxima;
  } params;

  /**
    * Type of the filter
    */
  image_amplifier_FILTER_TYPE type;

  /**
  * Type of the preprocessing
  */
  image_amplifier_PROCESS_TYPE method;

  /**
    * SizeOf the filter
    */
  unsigned filter_size;

  /**
    * Filtered image's scaling function.
    */
  image_amplifier_SCALE_FUNCTION scale;
} image_amplifier_OPTIONS;


/*************************************************************************/

/**
  * @brief improves the intensity of details
  * @details This function uses a Gaussian filter, which dismiss the details.
  *          After create the difference of the two image, this new image contains
  *          only the details. Thereafter summirize the original and the difference
  *          image, and the result is an image where the intensity of the details is 
  *          bigger.
  * @param input original image
  * @param options This parameter contains the open variables in the algorithm.
  * @param output already created image
  * @return The error code
  */
image_amplifier_ERROR_CODE
image_amplifier_details_up(const image_filter_IMG* input,
                           const image_amplifier_OPTIONS* options,
                           image_filter_IMG* output);

/****************************************************/

/**
  * @brief Simple scale function.
  * @details This scale function scale the image to the whole boundary [0,255]
  * @param input the input image
  * @param original the original image
  * @param out the scaled result
  */
void image_amplifier_scale(const image_filter_FILTER_GRID input,
                           const image_filter_IMG* original,
                           image_filter_IMG* out);

/****************************************************/

/**
  * @brief Simple scale function.
  * @details This scale function keeps the original minimum and maximum values,
  *          and scale the new image.
  * @param input the input image
  * @param original the original image
  * @param out the scaled result
  */
void image_amplifier_scale_to_origin(const image_filter_FILTER_GRID input,
                                     const image_filter_IMG* original,
                                     image_filter_IMG* out);

/****************************************************/

/**
  * @brief Simple scale function.
  * @details This scale function gets the avarige of the orignal and the
  *          result image. 
  *          After this it cuts the foo low or too high items.
  * @param input the input image
  * @param original the original image
  * @param out the scaled result
  */
void image_amplifier_avg_scale(const image_filter_FILTER_GRID input,
                               const image_filter_IMG* original,
                               image_filter_IMG* out);

/****************************************************/

/**
  * @brief Simple scale function.
  * @details This scale function cuts the lower or upper flow pixels.
  * @param input the input image
  * @param original the original image
  * @param out the scaled result
  */
void image_amplifier_cut_scale(const image_filter_FILTER_GRID input,
                               const image_filter_IMG* original,
                               image_filter_IMG* out);
#endif
