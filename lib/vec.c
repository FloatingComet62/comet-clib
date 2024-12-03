#include "../lib.h"

u32 vec_increase_capacity(const u32 old_capacity) {
  return old_capacity + max(old_capacity, COMET_LIB_VEC_MAX_INCREMENT);
}

vec vec_init(const u32 stride) {
  void* data =
      calloc("vector initialization", COMET_LIB_VEC_INITIAL_CAPACITY, stride);
  if (data == NULL) {
    errr("Failed to allocate memory");
  }
  return (vec){data, stride, 0, COMET_LIB_VEC_INITIAL_CAPACITY};
}

vec vec_init_reserve(const u32 stride, const u32 capacity) {
  void* data =
      calloc("vector initialization with reserved size", capacity, stride);
  if (data == NULL) {
    errr("Failed to allocate memory");
  }
  return (vec){data, stride, 0, capacity};
}

void vec_deinit(const vec self) { free("vector deinitialization", self.head); }

optional vec_at(vec* self, const u32 index) {
  if (index >= self->length) {
    return optional_init_none();
  }
  return optional_init_some((char*)self->head + index * self->stride);
}
void* vec_at_assume(vec* self, const u32 index) {
  return (char*)self->head + index * self->stride;
}

void vecMUT_swap(vec* self, const u32 index1, const u32 index2) {
  if (index1 >= self->length || index2 >= self->length) {
    // fuck you
    return;
  }
  void* temp =
      malloc("vector temporary swap variable initialization", self->stride);
  memcpy(temp, vec_at_assume(self, index1), self->stride);
  memcpy(vec_at_assume(self, index1), vec_at_assume(self, index2),
         self->stride);
  memcpy(vec_at_assume(self, index2), temp, self->stride);
  free("vector temporary swap variable deinitialization", temp);
}

void vecMUT_reserve(vec* self, const u32 capacity) {
  self->head =
      realloc("vector resize reservation", self->head, capacity * self->stride);
  if (self->head == NULL) {
    errr("Failed to allocate memory");
  }
  self->capacity = capacity;
}

void vecMUT_push(vec* self, const void* data) {
  if (self->length + 1 > self->capacity) {
    vecMUT_reserve(self, vec_increase_capacity(self->capacity));
  }
  vecMUT_push_assume_capacity(self, data);
}

void vecMUT_push_value(vec* self, const void* data) {
  if (self->length + 1 > self->capacity) {
    vecMUT_reserve(self, vec_increase_capacity(self->capacity));
  }
  vecMUT_push_value_assume_capacity(self, data);
}

void vecMUT_push_assume_capacity(vec* self, const void* data) {
  memcpy((char*)self->head + self->length * self->stride, data, self->stride);
  self->length++;
}

void vecMUT_push_value_assume_capacity(vec* self, const void* data) {
  memcpy((char*)self->head + self->length * self->stride, &data, self->stride);
  self->length++;
}

optional vecMUT_pop(vec* self) {
  if (self->length == 0) {
    return optional_init_none();
  }
  void* item = malloc("vector element popping", self->stride);
  memcpy(item, (char*)self->head + self->length * self->stride, self->stride);
  self->length--;
  return optional_init_some(item);
}

void vecMUT_remove_at(vec* self, const u32 index) {
  memcpy((char*)self->head + index * self->stride,
         (char*)self->head + (index + 1) * self->stride,
         (self->length - index) * self->stride);
  self->length--;
}

void vec_serialize(vec* self, FILE* file) {
  fwrite(&self->length, sizeof(u32), 1, file);
  fwrite(&self->capacity, sizeof(u32), 1, file);
  fwrite(&self->stride, sizeof(u32), 1, file);
  fwrite(self->head, self->stride, self->length, file);
}

void vec_deserialize(vec* self, FILE* file) {
  fread(&self->length, sizeof(u32), 1, file);
  fread(&self->capacity, sizeof(u32), 1, file);
  fread(&self->stride, sizeof(u32), 1, file);
  vecMUT_reserve(self, self->capacity);
  fread(self->head, self->stride, self->length, file);
}