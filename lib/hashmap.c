#include "../lib.h"

u32 hashmap_increase_capacity(const u32 old_capacity) {
  return old_capacity + max(old_capacity, COMET_LIB_HASHMAP_MAX_INCREMENT);
}

hashmap hashmap_init(const u32 value_stride) {
  hashmap self;
  self.capacity = COMET_LIB_HASHMAP_INITIAL_CAPACITY;
  self.length = 0;
  self.value_stride = value_stride;
  self.entries = malloc(self.capacity * sizeof(hashmap_entry));
  return self;
}

hashmap hashmap_init_reserve(const u32 value_stride, const u32 capacity) {
  hashmap self;
  self.capacity = capacity;
  self.length = 0;
  self.value_stride = value_stride;
  self.entries = malloc(self.capacity * sizeof(hashmap_entry));
  return self;
}

void hashmap_deinit(const hashmap self) {
  for (u32 i = 0; i < self.length; i++) {
    str_deinit(self.entries[i].key);
    if (self.entries[i].value != NULL) {
      free(self.entries[i].value);
    }
  }
  free(self.entries);
}

optional hashmap_get(hashmap* self, str* key) {
  for (u32 i = 0; i < self->length; i++) {
    if (str_eq(&self->entries[i].key, key)) {
      return optional_init_some((void*)&self->entries[i]);
    }
  }
  return optional_init_none();
}

void hashmapMUT_reserve(hashmap* self, const u32 capacity) {
  self->entries = realloc(self->entries, capacity * sizeof(hashmap_entry));
  if (self->entries == NULL) {
    errr("Failed to allocate memory");
  }
  self->capacity = capacity;
}

void hashmapMUT_set(hashmap* self, str* key, void* value) {
  if (self->length == self->capacity) {
    hashmapMUT_reserve(self, hashmap_increase_capacity(self->capacity));
  }
  hashmapMUT_set_assume_capacity(self, key, value);
}

void hashmapMUT_set_assume_new_item(hashmap* self, str* key, void* value) {
  if (self->length == self->capacity) {
    hashmapMUT_reserve(self, hashmap_increase_capacity(self->capacity));
  }
  hashmapMUT_set_assume_capacity_and_new_item(self, key, value);
}

void hashmapMUT_set_assume_capacity(hashmap* self, str* key, void* value) {
  optional entry = hashmap_get(self, key);
  if (!entry.has_data) {
    hashmapMUT_set_assume_capacity_and_new_item(self, key, value);
    return;
  }
  ((hashmap_entry*)entry.data)->value = malloc(self->value_stride);
  if (((hashmap_entry*)entry.data)->value == NULL) {
    errr("Failed to allocate memory");
  }
  memcpy(((hashmap_entry*)entry.data)->value, value, self->value_stride);
}

void hashmapMUT_set_assume_capacity_and_new_item(hashmap* self, str* key,
                                                 void* value) {
  self->entries[self->length].key = str_init(key->data);
  self->entries[self->length].value = malloc(self->value_stride);
  if (self->entries[self->length].value == NULL) {
    errr("Failed to allocate memory");
  }
  memcpy(self->entries[self->length].value, value, self->value_stride);
  self->length++;
}

void hashmapMUT_remove(hashmap* self, str* key) {
  for (u32 i = 0; i < self->length; i++) {
    if (str_eq(&self->entries[i].key, key)) {
      str_deinit(self->entries[i].key);
      if (self->entries[i].value != NULL) {
        free(self->entries[i].value);
      }
      for (u32 j = i; j < self->length - 1; j++) {
        self->entries[j] = self->entries[j + 1];
      }
      self->length--;
      return;
    }
  }
}

void hashmapMUT_clear(hashmap* self) {
  for (u32 i = 0; i < self->length; i++) {
    str_deinit(self->entries[i].key);
    if (self->entries[i].value != NULL) {
      free(self->entries[i].value);
    }
  }
  self->length = 0;
}

vec hashmap_keys(hashmap* self) {
  vec keys = vec_init(sizeof(str*));
  for (u32 i = 0; i < self->length; i++) {
    vecMUT_push_value(&keys, &self->entries[i].key);
  }
  return keys;
}

vec hashmap_values(hashmap* self) {
  vec values = vec_init(sizeof(void*));
  for (u32 i = 0; i < self->length; i++) {
    vecMUT_push_value(&values, &self->entries[i].value);
  }
  return values;
}