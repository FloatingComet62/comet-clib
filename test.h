#include "lib.h"

#define assert(x, y)   \
  if (!(x)) {          \
    printf("\n%s", y); \
    return false;      \
  }

bool test_str_init();
bool test_str_init_reserve();
bool test_str_concat();
bool test_str_concat_cstr();
bool test_str_at();
bool test_str_find();

bool test_hashmap_getter_setter();