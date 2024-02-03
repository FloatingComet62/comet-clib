#ifndef COMET_LIB_ITERATOR_INTERNAL
#define COMET_LIB_ITERATOR_INTERNAL

#include "lib.h"

typedef struct {
  u16 length;
  u8 stride;
  void* data;
} intIterator;

#endif