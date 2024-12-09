#define COMET_LIB_INTERNAL_MEMORY_LENS 1
#include "../lib.h"

void lens_clear_logs() {
  FILE* file = fopen(COMET_LIB_MEMORY_LOG, "w");
  fclose(file);
}

bool lens_highlight_leaks() {
  FILE* file = fopen(COMET_LIB_MEMORY_LOG, "r");

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
    } else if (action == '-') {
      // free
      for (int i = 0; i < addresses.length; i++) {
        if (strcmp(vec_at_assume(&addresses, i), address) == 0) {
          vecMUT_remove_at(&addresses, i);
        }
      }
    } else if (action == '=') {
      // realloc
      char to_address[17];
      for (int i = 0; i < 16; i++) {
        to_address[i] = line[i + 1 + 16 + 2];
      }
      to_address[16] = '\0';
      for (int i = 0; i < addresses.length; i++) {
        char* address_ptr = vec_at_assume(&addresses, i);
        if (strcmp(address_ptr, address) != 0) {
          continue;
        }
        for (int j = 0; j < 17; j++) {
          address_ptr[j] = to_address[j];
        }
      }
    }
  }
  fclose(file);

  file = fopen(COMET_LIB_MEMORY_LOG, "a");
  if (addresses.length == 0) {
    fprintf(file, "No leaks");

    vec_deinit(addresses);
    fclose(file);
    return false;
  }
  fprintf(file, "\nLeaked %d pointers\n", addresses.length);
  for (int i = 0; i < addresses.length; i++) {
    fprintf(file, "%s\n", (char*)vec_at_assume(&addresses, i));
  }
  fprintf(file, "\n");

  fclose(file);
  vec_deinit(addresses);
  return true;
}

void* lens_malloc(size_t size, const char* source_file, const u32 line_number,
                  const char* description) {
  void* ptr = malloc("lens malloc", size);
  FILE* file = fopen(COMET_LIB_MEMORY_LOG, "a");
  fprintf(file, "+%p malloc %zu %s:%d %s\n", ptr, size, source_file,
          line_number, description);
  fclose(file);
  return ptr;
}
void* lens_calloc(size_t count, size_t size, const char* source_file,
                  const u32 line_number, const char* description) {
  void* ptr = calloc("lens calloc", count, size);
  FILE* file = fopen(COMET_LIB_MEMORY_LOG, "a");
  fprintf(file, "+%p calloc %zux%zu %s:%d %s\n", ptr, count, size, source_file,
          line_number, description);
  fclose(file);
  return ptr;
}

void lens_free(void* block, const char* source_file, const u32 line_number,
               const char* description) {
  FILE* file = fopen(COMET_LIB_MEMORY_LOG, "a");
  fprintf(file, "-%p freed %s:%d %s", block, source_file, line_number,
          description);
  free("lens free", block);

  fprintf(file, "\n");
  fclose(file);
}

void* lens_realloc(void* block, size_t size, const char* source_file,
                   const u32 line_number, const char* description) {
  FILE* file = fopen(COMET_LIB_MEMORY_LOG, "a");
  void* ptr = realloc("lens realloc", block, size);
  fprintf(file, "=%p->%p realloc %zu %s:%d %s\n", block, ptr, size, source_file,
          line_number, description);
  fclose(file);
  return ptr;
}