#include "lib.h"

typedef struct {
  u16 length;
  u16 size; /* allocated size */
  u8 stride;
  void* data;
} intVec;

const u8 INITIAL_STRING_SIZE = 8;
const u8 MAX_RESIZE_INCREMENT = 32;

tVec* tVec_create(u8 stride) {
  intVec* this = malloc(sizeof *this);
  if (this == NULL) {
    err("Failed to allocate memory");
  }

  char* data = malloc(INITIAL_STRING_SIZE * stride);
  if (data == NULL) {
    err("Failed to allocate memory");
  }

  this->size = INITIAL_STRING_SIZE;
  this->stride = stride;
  this->length = 0;
  this->data = data;
  return this;
}
tVec* tVec_reserve(u8 stride, u16 length) {
  intVec* this = malloc(sizeof *this);
  if (this == NULL) {
    err("Failed to allocate memory");
  }

  char* data = malloc(length * stride);
  if (data == NULL) {
    err("Failed to allocate memory");
  }

  this->size = length;
  this->stride = stride;
  this->length = 0;
  this->data = data;
  return this;
}
void tVec_free(tVec* this) { free(this); }
u16 tVec_length(tVec* fake) { return ((intVec*)fake)->length; }
void tVecMUT_resize(tVec** fake_mut, u16 new_size) {
  intVec** this_mut = (intVec**)fake_mut;
  char* data = realloc((*this_mut)->data, new_size * (*this_mut)->stride);
  if (data == NULL) {
    err("Failed to allocate memory");
  }
  (*this_mut)->data = data;
}
void* tVec_at(tVec* fake, u16 index) {
  intVec* this = (intVec*)fake;
  return this->data + this->stride * index;
}
void* tVec_at_clone(tVec* fake, u16 index) {
  intVec* this = (intVec*)fake;
  void* data = malloc(this->stride);
  memcpy(data, tVec_at(this, index), this->stride);
  return data;
}
void tVecMUT_push(tVec** fake_mut, void* data) {
  intVec** this_mut = (intVec**)fake_mut;
  intVec* this = *this_mut;
  if (this->length + 1 > this->size) {
  }
}
void* tVecMUT_pop(tVec** this_mut);
void tVecMUT_append(tVec** fake_mut, tVec* fake_other) {
  intVec* this = (intVec*)*fake_mut;
  intVec* other = (intVec*)fake_other;
  if (this->stride != other->stride) {
    err("Cannot");
  }
}