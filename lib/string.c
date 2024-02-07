#include "lib.h"

typedef struct {
  u16 length;
  u16 size;
  char* data;
} intString;

void tStringMUT_resize(tString** this_mut, u8 new_size);

const u8 INITIAL_STRING_SIZE = 8;
const u8 MAX_RESIZE_INCREMENT = 32;

tString* tString_create() {
  intString* this = malloc(sizeof *this);
  if (this == NULL) {
    err("Failed to allocate memory");
  }

  char* data = malloc(INITIAL_STRING_SIZE * sizeof *data);
  if (data == NULL) {
    err("Failed to allocate memory");
  }

  this->size = INITIAL_STRING_SIZE;
  this->length = 0;
  this->data = data;
  return this;
}
tString* tString_reserve(u16 length) {
  intString* this = malloc(sizeof *this);
  if (this == NULL) {
    err("Failed to allocate memory");
  }

  char* data = malloc(length * sizeof *data);
  if (data == NULL) {
    err("Failed to allocate memory");
  }

  this->size = length;
  this->length = 0;
  this->data = data;
  return this;
}
tString* tString_create_str(char* c_str) {
  tString* str = tString_create();
  tStringMUT_concat_cstr(&str, c_str);
  return str;
}
void tString_free(tString* fake) {
  intString* this = (intString*)fake;
  free(this->data);
  free(this);
}
u16 tString_length(tString* this) { return ((intString*)this)->length; }
char* tString_chars(tString* this) { return ((intString*)this)->data; }
void tStringMUT_resize(tString** fake_mut, u8 new_size) {
  intString** this_mut = (intString**)fake_mut;
  char* data = realloc((*this_mut)->data, new_size * sizeof *data);
  if (data == NULL) {
    err("Failed to allocate memory");
  }
  (*this_mut)->data = data;
}
void concat(intString** fake_mut, u16 length, char* data) {
  intString* this = (intString*)*fake_mut;
  if (this->length + length > this->size) {
    tStringMUT_resize(fake_mut, this->size + this->length +
                                    min(MAX_RESIZE_INCREMENT, this->size));
    intString** this_mut = (intString**)fake_mut;
    intString* this = *this_mut;
  }
  char* start = this->data + this->length * sizeof *start;
  u8 i = 0;
  for (; data[i] != '\0'; i++) {
    start[i] = data[i];
  }
  start[i] = '\0';
  this->length += length;
}
void tStringMUT_concat_cstr(tString** fake_mut, char* c_str) {
  intString** this_mut = (intString**)fake_mut;
  u8 length = 0;
  for (; c_str[length] != '\0'; length++)
    ;
  concat(fake_mut, length, c_str);
}
void tStringMUT_concat(tString** fake_mut, tString* fake_str) {
  intString** this_mut = (intString**)fake_mut;
  intString* this = *this_mut;
  intString* str = (intString*)fake_str;
  concat(fake_mut, str->length, str->data);
}
void tStringMUT_concatF(tString** this_mut, tString* str) {
  tStringMUT_concat(this_mut, str);
  tString_free(str);
}
char tString_at(tString* this, u8 index) {}
tOptional* tString_find_char(tString* this, char char_to_find) {}
tVec* tString_find_chars(tString* this, char char_to_find) {}