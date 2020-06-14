#include <iostream>
#include <string>
#include "utils.h"

void Utils::panic(char const* const format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  exit(EXIT_FAILURE);
}

