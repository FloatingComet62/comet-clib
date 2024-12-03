#define COMET_LIB_FORCE_LOG 1

#include "lib.h"

#ifndef COMET_LIB_TEST

int main() {
#if COMET_LIB_DEBUG
  lens_clear_logs();
#endif

  FILE* file = fopen("map.bin", "rb");
  hashmap map = hashmap_init(0);
  hashmap_deserialize(&map, file);
  fclose(file);

  // hashmap map = hashmap_init(sizeof(u32));
  // u32 value = 42;
  str key = str_init("key");
  // hashmapMUT_set(&map, &key, &value);

  // FILE* file = fopen("map.bin", "wb");
  // hashmap_serialize(&map, file);
  // fclose(file);

  optional entry = hashmap_get(&map, &key);
  if (entry.has_data) {
    printf("Value: %d\n", *(u32*)((hashmap_entry*)entry.data)->value);
  } else {
    printf("FUCK");
  }

  str_deinit(key);
  hashmap_deinit(map);

#if COMET_LIB_DEBUG
  lens_highlight_leaks();
#endif
  return 0;
}

#endif
