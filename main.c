#include "lib.h"

#ifndef COMET_LIB_TEST

int main() {
  hashmap map = hashmap_init(sizeof(u32));
  u32 value = 42;
  str key = str_init("key");
  hashmapMUT_set(&map, &key, &value);
  optional entry = hashmap_get(&map, &key);
  if (entry.has_data) {
    printf("Value: %d\n", *(u32*)((hashmap_entry*)entry.data)->value);
  } else {
    printf("FUCK");
  }

  str_deinit(key);
  hashmap_deinit(map);
  return 0;
}

#endif
