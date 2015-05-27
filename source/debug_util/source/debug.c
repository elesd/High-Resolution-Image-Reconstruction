#include "../header/debug.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

static void trace(const char*);

static debug_util_TRACE_FUNTION g_trace = &trace;
static debug_util_LEVELS g_level = DEBUG_UTIL_LEVEL_NONE;


static void
trace (const char* txt)
{
  printf("%s", txt);
  fflush(stdout);
}

void 
debug_util_set_trace_function(debug_util_TRACE_FUNTION trace)
{
  g_trace = trace;
}

void
debug_util_set_level(const debug_util_LEVELS level)
{
  g_level = level;
}
static bool
level_is_active(int level)
{
  bool isActivate = false;
  if (g_level == DEBUG_UTIL_LEVEL_NONE)
    return false;
  if (level & DEBUG_UTIL_LEVEL_ERROR)      /* 1xxxxx */
  {
    isActivate = true;
  }
  else
  {
    isActivate = ((int)g_level - level) >= 0;
  }
  return isActivate;
}

void debug_util_trace(unsigned level,
                      const char* file, unsigned line,
                      const char* format, ...)
{
  if (level_is_active(level))
  {
    char formatted_str[DEBUG_UTIL_BUFFER_SIZE] = {0};
    char result[DEBUG_UTIL_BUFFER_SIZE] = {0};
    memset(result, 0, sizeof(char) * DEBUG_UTIL_BUFFER_SIZE);
    memset(formatted_str, 0, sizeof(char) * DEBUG_UTIL_BUFFER_SIZE);
    snprintf(formatted_str, DEBUG_UTIL_BUFFER_SIZE, 
             "# %s:%d: %s", file, line, format);
    {
      va_list arg_list;
      va_start(arg_list, format);
      vsnprintf(result,DEBUG_UTIL_BUFFER_SIZE, formatted_str, arg_list);
      va_end(arg_list);
      (*g_trace)(result);
    }
  }
}

void
debug_util_trace_element(unsigned level, const char* file,
                         unsigned line, void* element,
                         debug_util_ELEMENT_TRACE_FUNTION function)
{
  if (level_is_active(level))
  {
    char formatted_str[DEBUG_UTIL_BUFFER_SIZE] = {0};
    char buffer[DEBUG_UTIL_BUFFER_SIZE] = {0};

    (*function)(element, buffer);
    
    snprintf(formatted_str, DEBUG_UTIL_BUFFER_SIZE, 
             "# %s:%d: %s", file, line, buffer);
    (*g_trace)(formatted_str);
  }
}
