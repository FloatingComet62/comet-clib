#include "../test.h"

bool test_hashmap_getter_setter() {
  hashmap map = hashmap_init(sizeof(u32));
  u32 value = 42;
  str key = str_init("key");
  hashmapMUT_set(&map, &key, &value);
  optional entry = hashmap_get(&map, &key);

  assert(entry.has_data, "Entry should have data");
  assert(*(u32*)((hashmap_entry*)entry.data)->value == 42,
         "Value should be 42");

  str_deinit(key);
  hashmap_deinit(map);
  return true;
}