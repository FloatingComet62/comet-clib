#ifndef COMET_LIB_VEC_INTERNAL
#define COMET_LIB_VEC_INTERNAL

#include "lib.h"

typedef struct {
  u16 length;
  u16 size; /* allocated size */
  u8 stride;
  void* data;
} tVec;

#endif