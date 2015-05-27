/**
* @file image_filter.h
* Image filter function.
*/
#ifndef IMAGE_FILTER_H
#define IMAGE_FILTER_H


/** @nodoc */
#define IMAGE_FILTER_OK 0

/** @nodoc */
#define IMAGE_FILTER_FILTER_ERROR -10

/**
  * @see image_filter_FILTER
  */
#define IMAGE_FILTER_FILTER_TYPE_MASK 0

/**
  * @see image_filter_FILTER
  */
#define IMAGE_FILTER_FILTER_TYPE_FUNCTION 1
/****************************************************/
/** @nodoc */
typedef unsigned char image_filter_IMG_DATA;

/** @nodoc */
typedef double image_filter_MASK_DATA;

/** @nodoc */
typedef int image_filter_ERROR_CODE;

/** @nodoc */
typedef image_filter_IMG_DATA* image_filter_DATA_GRID;

/** @nodoc */
typedef image_filter_MASK_DATA* image_filter_FILTER_GRID;

/** @nodoc */
typedef image_filter_MASK_DATA* image_filter_MASK_GRID;
/****************************************************/
/**
  * @brief filtering function
  * @details This function do the filtering in the image
  * @param img_data the image data in the x, y coodinates
  * @param x the x coordinate on the current window
  * @param y the y coordinate on the current window
  * @param size the size of the filter
  */
typedef image_filter_MASK_DATA
  (*image_filter_FILTER_FUNCTION)(const image_filter_IMG_DATA img_data,
                                  const double x,
                                  const double y,
                                  const unsigned size);

/****************************************************/

/**
  * @brief Function which returns a mask value.
  * @param x the x window coordinate
  * @param y the y window coordinate
  * @return the mask value
  */
typedef image_filter_MASK_DATA
  (*image_filter_MASK_FUNCTION)(const double x,
                                const double y);

/****************************************************/

/**
  * @brief Enumeration of the image filters
  */
typedef enum
{
  MASK,
  FUNCTION
} image_filter_MODE;

/****************************************************/

/**
  * @brief Filter object
  * @details It could be work based on a mask or based on a 
  *          mathematical function.
  */
typedef struct 
{
  /** Size of the filter */
  unsigned size;
  /** Used filter */
  union
  {
    /** Filter which given as a mask */
    image_filter_MASK_GRID mask;
    /** Filter which given as a function */
    image_filter_FILTER_FUNCTION function;
  } filter;
  /** The filter mode */
  image_filter_MODE mode;
} image_filter_FILTER;

/****************************************************/

/**
  * @brief image object in this context.
  */
typedef struct
{
  /** width of the image */
  unsigned width;
  /** height of the image */
  unsigned height;
  /** The data grid */
  image_filter_DATA_GRID content;
} image_filter_IMG;


/****************************************************/

/**
  * @brief Applies the given mask on the given image
  * @details This function creates the output grid
  *          based on the given input image, and 
  *          applies the given mask.
  * @param img the input image
  * @param filter the applied filter
  * @param out output parameter, created inside the function.
  * @return the error code.
  */
image_filter_ERROR_CODE
image_filter_apply_filter(const image_filter_IMG* img,
                          const image_filter_FILTER* filter,
                          image_filter_FILTER_GRID out);

/****************************************************/

/**
  * @brief Creates an image structure.
  * @param width the width of the image
  * @param height the height of the image
  * @param out the result image
  * @return the error code
  */
void
image_filter_create_image(const unsigned width,
                          const unsigned height,
                          image_filter_IMG* out);

/****************************************************/

/**
  * @brief Creates a filter structure.
  * @details A mask always contains integers,
  *          if you want to use double use the
  *          functional way. 
  *          The size have to be odd.
  * @see image_filter_create_filter_by_function
  * @param size the size of the mask. Only odd is supported.
  * @param mask the mask matrix. If it is NULL the content won't be filled
  * @param out the result mask
  */
void
image_filter_create_filter_by_mask(const unsigned size,
                                   image_filter_MASK_GRID mask,
                                   image_filter_FILTER* out);

/****************************************************/

/**
  * @brief Creates a filter structure.
  * @details A mask always contains integers,
  *          if you want to use double use the
  *          functional way. 
  *          The size have to be odd.
  * @see image_filter_create_filter_by_function
  * @param size the size of the mask. Only odd is supported.
  * @param mask the mask matrix. If it is NULL the content won't be filled
  * @param out the result mask
  * @return the error code
  */
void
image_filter_create_filter_by_function(const unsigned size,
                                       image_filter_MASK_FUNCTION mask,
                                       image_filter_FILTER* out);

/****************************************************/

/**
  * @brief Creates a filter structure.
  * @details Creates a filter which content will be the given function. 
  *          The size have to be odd.
  * @see image_filter_create_filter_by_function
  * @param size the size of the mask. Only odd is supported.
  * @param filter filter function
  * @param out the result mask
  */
void
image_filter_create_filter_function(const unsigned size,
                                    image_filter_FILTER_FUNCTION filter,
                                    image_filter_FILTER* out);

/****************************************************/

/**
  * @brief Destroy the filter object
  * @details This function free the memory above the object, also
  * destroy the mask memory!
  * @param filter filter to destroy
  */
void
image_filter_destroy_filter(image_filter_FILTER* filter);

/****************************************************/

/**
  * @brief Destroy the image object
  * @details This function free the memory above the object
  * @param img image to destroy
  */
void
image_filter_destroy_image(image_filter_IMG* img);

/****************************************************/

/**
* @brief Copy image.
* @return The copy of the given image.
*/
image_filter_IMG
image_filter_copy(const image_filter_IMG*);

/****************************************************/

/**
* @brief Copy image to the given memory place.
* @param dest: allocated memory place of the copy
* @param element: element to copy
*/
void
image_filter_copy_to(image_filter_IMG* dest, 
                     const image_filter_IMG* const element);
#endif
