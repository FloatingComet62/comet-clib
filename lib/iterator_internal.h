#ifndef COMET_LIB_OPTIONAL_INTERNAL
#define COMET_LIB_OPTIONAL_INTERNAL

#include "lib.h"

typedef struct {
  u16 length;
  u8 stride;
  void* data;
} tIterator;

#endif