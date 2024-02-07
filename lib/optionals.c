#include "lib.h"

typedef struct {
  bool has_data;
  u8 size_of_data;
  void* data;
} intOptional;

tOptional* tOptional_create(void* data, u8 size_of_data) {
  intOptional* this = malloc(sizeof *this + size_of_data);
  if (this == NULL) {
    err("Failed to allocate memory");
  }
  this->has_data = true;
  this->size_of_data = size_of_data;
  this->data = data;
  return this;
}
tOptional* tOptional_create_clone(void* data, u8 size_of_data) {
  intOptional* this = malloc(sizeof *this + size_of_data);
  if (this == NULL) {
    err("Failed to allocate memory");
  }
  this->has_data = true;
  this->size_of_data = size_of_data;
  this->data = (void*)((char*)this + sizeof *this);
  memcpy(this->data, data, size_of_data);
  return this;
}
tOptional* tOptional_create_none() {
  intOptional* this = malloc(sizeof *this);
  if (this == NULL) {
    err("Failed to allocate memory");
  }
  this->has_data = false;
  this->size_of_data = 0;
  this->data = NULL;
  return this;
}
void tOptional_free(tOptional* this) { free(this); }
bool tOptional_is_some(tOptional* this) {
  return ((intOptional*)this)->has_data;
}
bool tOptional_is_none(tOptional* this) {
  return !((intOptional*)this)->has_data;
}
void* tOptional_unwrap(tOptional* fake) {
  intOptional* this = (intOptional*)fake;
  if (!this->has_data) {
    err("Unwrapped optional into a `None` Varient");
  }
  return this->data;
}
void* tOptional_unwrap_clone(tOptional* fake) {
  intOptional* this = (intOptional*)fake;
  void* data = malloc(this->size_of_data);
  memcpy(data, tOptional_unwrap(this), this->size_of_data);
  return data;
}
void* tOptional_unwrapF(tOptional* fake) {
  intOptional* this = (intOptional*)fake;
  if (!this->has_data) {
    err("Unwrapped optional into a `None` Varient");
  }
  // void* response;
  // memcpy(response, this->data, this->size_of_data);
  void* response = this->data;
  tOptional_free(this);
  return response;
}
void* tOptional_unwrap_cloneF(tOptional* this) {
  void* data = tOptional_unwrap_clone(this);
  tOptional_free(this);
}