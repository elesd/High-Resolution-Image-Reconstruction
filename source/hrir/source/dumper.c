#include "../header/dumper.h"

#include <stdio.h>

dumper_ERROR_CODE
dumper_trace_to_file(const char* file_name,
                     const void* data,
                     unsigned length)
{
  FILE* file = fopen(file_name, "wb");
  dumper_ERROR_CODE ret = DUMPER_OK;
  if (file == NULL)
    ret = DUMPER_FILE_OPEN_ERROR;
  else
  {
    size_t writen = fwrite(data, 1, length, file);
    if (writen != length)
      ret = DUMPER_WRITE_ERROR;
    fclose(file);
  }
  return ret;
}

