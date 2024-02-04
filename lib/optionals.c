#include "optionals_internal.h"

tOptional* tOptional_create(void* data, u8 size_of_data) {
  intOptional* obj = malloc(sizeof *obj + size_of_data);
  if (obj == NULL) {
    err("Failed to allocate memory");
  }
  obj->has_data = true;
  obj->size_of_data = size_of_data;
  obj->data = data;
  return obj;
}
tOptional* tOptional_create_clone(void* data, u8 size_of_data) {
  intOptional* obj = malloc(sizeof *obj + size_of_data);
  if (obj == NULL) {
    err("Failed to allocate memory");
  }
  obj->has_data = true;
  obj->size_of_data = size_of_data;
  obj->data = (void*)((char*)obj + sizeof *obj);
  memcpy(obj->data, data, size_of_data);
  return obj;
}
tOptional* tOptional_create_none() {
  intOptional* obj = malloc(sizeof *obj);
  if (obj == NULL) {
    err("Failed to allocate memory");
  }
  obj->has_data = false;
  obj->size_of_data = 0;
  obj->data = NULL;
  return obj;
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
void* tOptional_unwrap_clone(tOptional* this) {}
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
void* tOptional_unwrap_cloneF(tOptional* this) {}