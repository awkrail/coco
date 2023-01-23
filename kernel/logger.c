#include "logger.h"

#include <stddef.h>
#include <stdio.h>

#include "console.h"

enum LogLevel log_level = kWarn;
extern struct Console* console;

void SetLogLevel(enum LogLevel level)
{
  log_level = level;
}

int Log(enum LogLevel level, const char* format, ...)
{
  if(level < log_level)
    return 0;

  va_list ap;
  int result;
  char s[1024];

  va_start(ap, format);
  result = vsprintf(s, format, ap);
  va_end(ap);

  PutString(console, s);
  return result;
}
