#include "../test.h"

void test_func(bool (*fun_ptr)(), const char* function_name) {
  printf("Testing \033[1;33m%s\033[0m ...", function_name);
  if (fun_ptr()) {
    printf(" \033[1;32mpassed\033[0m\n");
  } else {
    printf(" ... \033[1;31mfailed\033[0m\n");
  }
}

int main() {
  test_func(&test_str_init, "str:init");
  test_func(&test_str_init_reserve, "str:init_reserve");
  test_func(&test_str_concat, "str:concat");
  test_func(&test_str_concat_cstr, "str:concat_cstr");
  test_func(&test_str_at, "str:at");
  test_func(&test_str_find, "str:find");
  test_func(&test_hashmap_getter_setter, "hashmap:getter_setter");
  return 0;
}
