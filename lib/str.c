#include "../lib.h"

u32 str_increase_capacity(const u32 old_capacity) {
  return old_capacity + max(old_capacity, COMET_LIB_STR_MAX_INCREMENT);
}

u32 cstr_len(const char* data) {
  u32 length = 0;
  while (data[length] != '\0') {
    length++;
  }
  return length;
}

str str_init(const char* data) {
  str self;
  self.length = cstr_len(data);
  self.capacity = max(COMET_LIB_STR_INITIAL_CAPACITY, self.length);
  self.data = calloc(self.capacity, sizeof(char));
  if (self.data == NULL) {
    errr("Failed to allocate memory");
  }
  u32 i = 0;
  for (; i < self.length; i++) {
    self.data[i] = data[i];
  }
  self.data[i] = '\0';

  return self;
}

str str_init_reserve(const u32 capacity) {
  str self;
  self.capacity = capacity;
  self.length = 0;
  self.data = calloc(capacity, sizeof(char));
  if (self.data == NULL) {
    errr("Failed to allocate memory");
  }
  return self;
}

void str_deinit(const str self) { free(self.data); }

str str_concat(str* str1, str* str2) {
  u32 new_len = str1->length + str2->length;
  u32 new_capacity = str1->capacity + str2->capacity;
  char* new_data = malloc(new_capacity * sizeof(char));
  if (new_data == NULL) {
    errr("Failed to allocate memory");
  }
  u32 i = 0;
  for (; i < new_len; i++) {
    if (i < str1->length) {
      new_data[i] = str1->data[i];
      continue;
    }
    new_data[i] = str2->data[i - str1->length];
  }
  new_data[i] = '\0';
  return (str){new_data, new_len, new_capacity};
}

str str_concat_cstr(str* str1, const char* str2) {
  u32 str2_length = cstr_len(str2);
  u32 new_len = str1->length + str2_length;
  u32 new_capacity = str1->capacity + str2_length;
  char* new_data = calloc(new_capacity, sizeof(char));
  if (new_data == NULL) {
    errr("Failed to allocate memory");
  }
  u32 i = 0;
  for (; i < new_len; i++) {
    if (i < str1->length) {
      new_data[i] = str1->data[i];
      continue;
    }
    new_data[i] = str2[i - str1->length];
  }
  new_data[i] = '\0';
  return (str){new_data, new_len, new_capacity};
}

optional str_at(str* self, const u32 index) {
  if (index >= self->length) {
    return optional_init_none();
  }
  return optional_init_some((void*)(size_t)self->data[index]);
}

optional str_find(str* self, const char character) {
  for (u32 i = 0; i < self->length; i++) {
    if (self->data[i] != character) {
      continue;
    }
    return optional_init_some((void*)(size_t)i);
  }
  return optional_init_none();
}

bool str_eq(str* str1, str* str2) {
  if (str1->length != str2->length) {
    return false;
  }
  for (u32 i = 0; i < str1->length; i++) {
    if (str1->data[i] != str2->data[i]) {
      return false;
    }
  }
  return true;
}

void strMUT_reserve(str* self, const u32 capacity) {
  self->data = realloc(self->data, capacity * sizeof(char));
  if (self->data == NULL) {
    errr("Failed to allocate memory");
  }
  self->capacity = capacity;
}

void strMUT_concat(str* str1, str* str2) {
  if (str1->length + str2->length > str1->capacity) {
    strMUT_reserve(str1, str_increase_capacity(str1->capacity));
  }
  strMUT_concat_assume_capacity(str1, str2);
}

void strMUT_concat_cstr(str* str1, const char* str2) {
  u32 str2_length = cstr_len(str2);
  if (str1->length + str2_length > str1->capacity) {
    strMUT_reserve(str1, str_increase_capacity(str1->capacity));
  }
  strMUT_concat_cstr_assume_capacity(str1, str2);
}

void strMUT_remove_at(str* self, const u32 index) {
  for (u32 i = index; i < self->length; i++) {
    self->data[i] = self->data[i + 1];
  }
  self->length--;
}

void strMUT_concat_assume_capacity(str* str1, str* str2) {
  u32 i = str1->length;
  for (; i < str1->length + str2->length; i++) {
    str1->data[i] = str2->data[i - str1->length];
  }
  str1->data[i] = '\0';
}

void strMUT_concat_cstr_assume_capacity(str* str1, const char* str2) {
  u32 str2_length = cstr_len(str2);
  u32 i = str1->length;
  for (; i < str1->length + str2_length; i++) {
    str1->data[i] = str2[i - str1->length];
  }
  str1->data[i] = '\0';
}

void str_serialize(str* self, FILE* file) {
  fwrite(&self->length, sizeof(u32), 1, file);
  fwrite(&self->capacity, sizeof(u32), 1, file);
  fwrite(self->data, sizeof(char), self->length, file);
}

void str_deserialize(str* self, FILE* file) {
  fread(&self->length, sizeof(u32), 1, file);
  fread(&self->capacity, sizeof(u32), 1, file);
  strMUT_reserve(self, self->capacity);
  fread(self->data, sizeof(char), self->length, file);
}