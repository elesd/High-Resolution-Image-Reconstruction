/**
* @file haar_transformation.h
* This file contains functions for the haar transformation 
*/
#ifndef HAAR_TRANSFORMATION_H
#define HAAR_TRANSFORMATION_H


/***********************************************************/
/** @nodoc */
typedef unsigned char* haar_transformation_DATA_GRID;

/***********************************************************/
/**
  * @brief data source of the transformation
  */
typedef struct
{
  /** Width of the data image */
  unsigned width;
  /** Height of the data image */
  unsigned height;
  /** The original image */
  haar_transformation_DATA_GRID original_image;
  /** The image of average (in half size) */
  haar_transformation_DATA_GRID avg_image;
  /** Vertical edges (in half size) */
  haar_transformation_DATA_GRID vertical_edges;
  /** Horizontal edges (in half size) */
  haar_transformation_DATA_GRID horizontal_edges;
  /** Diagonal edges (in half size) */
  haar_transformation_DATA_GRID diagonal_edges;
} haar_transformation_DATA_SOURCE;

/***********************************************************/
/**
  * @brief Transformation
  * The all resoult is half times as the original
  * @param data_source The data source
  */
void
haar_transformation_transform
(
  haar_transformation_DATA_SOURCE data_source
);

/**
  * @brief Inverse transformation
  * The all resoult is half times as the original
  * @param data_source The data source
  */
void 
haar_transformation_inverse_transformation
(
  haar_transformation_DATA_SOURCE data_source
);

#endif

