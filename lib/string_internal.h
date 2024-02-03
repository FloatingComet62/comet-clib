#ifndef COMET_LIB_STRING_INTERNAL
#define COMET_LIB_STRING_INTERNAL

#include "lib.h"

typedef struct {
  u16 length;
  u16 size;
  char* data;
} intString;

void tStringMUT_resize(tString** this_mut, u8 new_size);

#endif