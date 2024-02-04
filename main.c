#define DEBUG 0

#include "lib/lib.h"

typedef struct {
  u32 yo_mama;
  u32 so_fat;
  u64 she_a_u128;
} s;

int main(int argc, char** argv) {
  // tString* str = tString_create_str("Hello World");
  // tStringMUT_concat_cstr(&str, " concat me");
  // log_infoF(str); // Hello World concat me

  // tOptional* optional = tOptional_create_none();
  // printf("%d\n", tOptional_is_some(optional)); // 0

  tOptional* optional;
  {
    s thing;
    thing.she_a_u128 = 33;

    optional = tOptional_create_clone((void*)&thing, sizeof thing);
    thing.she_a_u128 = 34;
  }

  printf("%d\n", ((s*)tOptional_unwrapF(optional))->she_a_u128);  // 33

  info("Exiting");
  return 0;
}
