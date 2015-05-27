/**
  * @file debug.h
  * This file is the main file of debug.
  * Use this module only with macros, like
  * DEBUG_UTIL_TRACE, DEBUG_UTIL_ERROR, DEBUG_UTIL_DEBUG.
  * For activate traces you have to define the DEBUG_UTIL_ACTIVATE, 
  * without it, this module has no effect.
  */

#ifndef DEBUG_UTIL_H
#define DEBUG_UTIL_H

#define DEBUG_UTIL_BUFFER_SIZE 4096

#ifdef DEBUG_UTIL_ACTIVATE
#  define DEBUG_UTIL_TRACE(level, format, ...)\
     debug_util_trace(DEBUG_UTIL_LEVEL_TRACE + level,\
                      __FILE__, __LINE__, format, __VA_ARGS__)
#  define DEBUG_UTIL_DEBUG(level, format, ...)\
     debug_util_trace(DEBUG_UTIL_LEVEL_DEBUG + level,\
                      __FILE__, __LINE__, format, __VA_ARGS__)
#  define DEBUG_UTIL_ERROR(format, ...)\
     debug_util_trace(DEBUG_UTIL_LEVEL_ERROR,\
                      __FILE__, __LINE__, format, __VA_ARGS__)
#  define DEBUG_UTIL_TRACE_ELEMENT(level, element, function)\
     debug_util_trace_element(level, __FILE__,\
                              __LINE__, element, function)
#else
/**
* Trace macro.
* Trace will be visible if a higher or the given level is active.
* @param level: level of the traced information, from 0 till 14
* @param format: format of the output
*/
#  define DEBUG_UTIL_TRACE(level, format, ...)
/**
* Debug macro.
* Trace will be visible if a higher or the given level is active.
* @param level: level of the traced information, from 0 till 14
* @param format: format of the output
*/
#  define DEBUG_UTIL_DEBUG(level, format, ...)
/**
* Error macro.
* Trace will be visible always, if DEBUG_UTIL_ACTIVATE is defined.
* @param level: level of the traced information, from 0 till 14
* @param format: format of the output
*/
#  define DEBUG_UTIL_ERROR(level, format, ...)
/**
* Trace an element with the given function
* @param level legel of the trace
* @param element the object to trace
* @param function function wich can trace an element.
* @see #debug_util_ELEMENT_TRACE_FUNTION
*/
#  define DEBUG_UTIL_TRACE_ELEMENT(level, element, function)
#endif

/**
* Debug level definitions.
* @code 
*   DEBUG_UTIL_LEVEL_TRACE + 1
* @endcode
*/
typedef enum
{
  DEBUG_UTIL_LEVEL_NONE = 0,   /**< 000000 Disable debug */
  DEBUG_UTIL_LEVEL_TRACE = 1,  /**< 000001 Trace levels, there are 14 */
  DEBUG_UTIL_LEVEL_DEBUG = 16, /**< 010000 Debug levels, there are 15 */
  DEBUG_UTIL_LEVEL_ERROR = 32  /**< 100000 Error levels, unlimited */
} debug_util_LEVELS;

/**
* Trace function
*/
typedef void (*debug_util_TRACE_FUNTION)(const char *);

/**
* function which prints its result to the given buffer
* @param element element to trace
* @param buffer Buffer to store the trace content
*/
typedef void (*debug_util_ELEMENT_TRACE_FUNTION)(void* element,
  char buffer[DEBUG_UTIL_BUFFER_SIZE]);

/**
* Setter function for trace
*/
void 
debug_util_set_trace_function(debug_util_TRACE_FUNTION trace);

/**
* Set the current debug level
* @param level: Activate the given level
*/
void
debug_util_set_level(const debug_util_LEVELS level);

/**
* Debug function.
* @param level: Level of the trace
* @param file: current file.
* @param line: current line.
* @param format: Output format.
*/
void
debug_util_trace(unsigned level, const char* file, 
                 unsigned line, const char* format, ...);

/**
* Trace function for different kind of elements
* @param level: Level of the trace
* @param file: current file.
* @param line: current line.
* @param element: element to trace
* @param function: the way of the trace
*/
void
debug_util_trace_element(unsigned level, const char* file,
                         unsigned line, void* element,
                         debug_util_ELEMENT_TRACE_FUNTION function);

#endif
