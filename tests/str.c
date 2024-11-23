#include <string.h>

#include "../test.h"

struct malloc_size_response {
  bool exists;
  u32 size;
};

#if defined(__linux__)
// https://linux.die.net/man/3/malloc_usable_size
#include <malloc.h>
struct malloc_size_response malloc_size(const void *p) {
  return (struct malloc_size_response){true, malloc_usable_size((void *)p)};
}
#elif defined(__APPLE__)
// https://www.unix.com/man-page/osx/3/malloc_size/
#include <malloc/malloc.h>
struct malloc_size_response malloc_size(const void *p) {
  return (struct malloc_size_response){true, malloc_size(p)};
}
#elif defined(_WIN32)
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/msize
#include <malloc.h>
struct malloc_size_response malloc_size(const void *p) {
  return (struct malloc_size_response){true, _msize((void *)p)};
}
#else
struct malloc_size_response malloc_size(const void *p) {
  return (struct malloc_size_response){false, 0};
}
#endif

bool test_str_init() {
  str s = str_init("Hello World");
  assert(strcmp(s.data, "Hello World") == 0,
         "String doesn't contain correct data");
  assert(s.length == 11, "String length is incorrectly assigned");
  str_deinit(s);
  return true;
}

bool test_str_init_reserve() {
  str s = str_init_reserve(100);
  assert(s.capacity == 100, "Incorrect capacity assigned");
  struct malloc_size_response msize = malloc_size(s.data);
  if (msize.exists) {
    // it's fine if it's a little over allocated, linux does that
    assert(msize.size >= 100 * sizeof(char), "Incorrect malloc size allocated");
  }
  str_deinit(s);
  return true;
}

bool test_str_concat() {
  str s1 = str_init("Hello ");
  str s2 = str_init("World");
  str s3 = str_concat(&s1, &s2);
  assert(strcmp(s3.data, "Hello World") == 0, "Incorrect concatination");
  assert(s3.length == 11, "Incorrect length assignment");
  str_deinit(s3);
  str_deinit(s1);
  str_deinit(s2);
  return true;
}

bool test_str_concat_cstr() {
  str s1 = str_init("Hello ");
  str s2 = str_concat_cstr(&s1, "World");
  assert(strcmp(s2.data, "Hello World") == 0, "Incorrect concatination");
  assert(s2.length == 11, "Incorrect length assignment");
  str_deinit(s2);
  str_deinit(s1);
  return true;
}

bool test_str_at() {
  str s = str_init("Hello World");
  assert(((char)(size_t)str_at(&s, 6).data) == 'W', "Incorrect indexing");
  str_deinit(s);
  return true;
}

bool test_str_find() {
  str s = str_init("Hello World");
  assert(((u32)(size_t)str_find(&s, 'W').data) == 6, "Incorrect indexing");
  str_deinit(s);
  return true;
}
