#ifndef COMET_LIB_OPTIONAL_INTERNAL
#define COMET_LIB_OPTIONAL_INTERNAL

#include "lib.h"

typedef struct {
  bool has_data;
  u8 size_of_data;
  void* data;
} intOptional;

#endif