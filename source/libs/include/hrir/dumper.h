/**
* @file dumper.h
* Functions for dump data to a file
*/
#ifndef DUMPER_H
#define DUMPER_H

#include <stdio.h>
/** @nodoc */
#define DUMPER_OK 0
/** @nodoc */
#define DUMPER_FILE_OPEN_ERROR -1
/** @nodoc */
#define DUMPER_WRITE_ERROR -2

/******************************************************************************/

/** @nodoc */
typedef int dumper_ERROR_CODE;

/******************************************************************************/

/**
* @brief Dump the file content to file
* @param file_name output file name
* @param data the data to print out
* @param length length of data
* @return dumper error code
*/
dumper_ERROR_CODE
dumper_trace_to_file(const char* file_name,
                     const void* data, 
                     unsigned length);
                  

#define DUMPER_TRACE_IMAGE(data, width, height) { \
  char TRACE_IMAGE_tmp[128];snprintf(TRACE_IMAGE_tmp, 128, "%s_%d_%d", #data, width, height);\
  dumper_trace_to_file(TRACE_IMAGE_tmp, data, width * height);}

#endif /* DUMPER_H */
