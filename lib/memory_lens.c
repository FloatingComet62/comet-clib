#define COMET_LIB_INTERNAL_MEMORY_LENS 1
#include "../lib.h"

void lens_clear_logs() {
  FILE* file = fopen("memory.log", "w");
  fclose(file);
}

void lens_highlight_leaks() {
  FILE* file = fopen("memory.log", "r");

  vec addresses = vec_init(17 * sizeof(char));
  char address_to_ignore[17];
  sprintf(address_to_ignore, "%p", addresses.head);
  address_to_ignore[16] = '\0';

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    char action = line[0];

    char address[17];
    for (int i = 0; i < 16; i++) {
      address[i] = line[i + 1];
    }
    address[16] = '\0';

    if (strcmp(address_to_ignore, address) == 0) {
      continue;
    }

    if (action == '+') {
      // allocation
      vecMUT_push(&addresses, address);
    }
    if (action != '-') {
      // mkc
      continue;
    }
    // free
    for (int i = 0; i < addresses.length; i++) {
      if (strcmp(vec_at_assume(&addresses, i), address) == 0) {
        vecMUT_remove_at(&addresses, i);
      }
    }
  }
  fclose(file);

  if (addresses.length == 0) {
    vec_deinit(addresses);
    return;
  }
  file = fopen("memory.log", "a");
  fprintf(file, "\nLeaked %d pointers\n", addresses.length);
  for (int i = 0; i < addresses.length; i++) {
    fprintf(file, "%s\n", vec_at_assume(&addresses, i));
  }
  fprintf(file, "\n");
  fclose(file);

  vec_deinit(addresses);
}

void* lens_malloc(size_t size, const char* source_file, const u32 line_number) {
  void* ptr = malloc(size);
  FILE* file = fopen("memory.log", "a");
  fprintf(file, "+%p malloc %d %s:%d\n", ptr, size, source_file, line_number);
  fclose(file);
  return ptr;
}
void* lens_calloc(size_t count, size_t size, const char* source_file,
                  const u32 line_number) {
  void* ptr = calloc(count, size);
  FILE* file = fopen("memory.log", "a");
  fprintf(file, "+%p calloc %dx%d %s:%d\n", ptr, count, size, source_file,
          line_number);
  fclose(file);
  return ptr;
}

void lens_free(void* block, const char* source_file, const u32 line_number) {
  FILE* file = fopen("memory.log", "a");
  fprintf(file, "-%p freed %s:%d", block, source_file, line_number);
  free(block);

  fprintf(file, "\n");
  fclose(file);
}